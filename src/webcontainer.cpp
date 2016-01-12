#include "webcontainer.h"
#include "tabhost.h"
#include "webpage.h"

#include <QRegularExpression>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QWebEngineView>
#include <QWebEngineProfile>

WebContainer::WebContainer(TabHost* tabHost, QWidget* parent)
    : QWidget(parent),
      tabHost(tabHost),
      mainLayout(new QVBoxLayout),
      locationEdit(new QLineEdit(this)),
      webView(new QWebEngineView(this))
{
    this->setLayout(this->mainLayout);

    QHBoxLayout* locationLayout = new QHBoxLayout;

    // Back button
    QPushButton* backButton = new QPushButton(QIcon::fromTheme("go-previous"), "", this);
    connect(backButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Back);
    });
    locationLayout->addWidget(backButton);

    // Forward button
    QPushButton* forwardButton = new QPushButton(QIcon::fromTheme("go-next"), "", this);
    connect(forwardButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Forward);
    });
    locationLayout->addWidget(forwardButton);

    // Refresh button
    QPushButton* refreshButton = new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    connect(refreshButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Reload);
    });
    locationLayout->addWidget(refreshButton);

    // Location edit
    locationLayout->addWidget(this->locationEdit);

    // Settings button
    QToolButton* settingsButton = new QToolButton(this);
    settingsButton->setIcon(QIcon::fromTheme("configure"));
    settingsButton->setToolTip(tr("Settings"));
    settingsButton->setMenu(this->tabHost->getSettingsMenu());
    settingsButton->setPopupMode(QToolButton::InstantPopup);
    locationLayout->addWidget(settingsButton);

    this->mainLayout->addLayout(locationLayout);

    connect(this->locationEdit, &QLineEdit::returnPressed, [this]()
    {
        QString path = this->locationEdit->text();
        if (!path.contains(":"))
        {
            if (path.contains(".") && !path.contains(QRegularExpression("/s")))
                path.prepend("http://");
            else
                path = "http://google.com/search?pws=0&q=" + QUrl::toPercentEncoding(path);
        }
        this->locationEdit->setText(path);
        this->webView->load(QUrl(path, QUrl::TolerantMode));
    });

    connect(this->webView, &QWebEngineView::urlChanged, [this](QUrl url)
    {
        this->locationEdit->setText(url.url());
        this->locationEdit->setCursorPosition(0);
    });

    this->webView->setPage(new WebPage(this->tabHost, this));
    this->webView->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    this->mainLayout->addWidget(this->webView);
}

QWebEngineView* WebContainer::getWebView() const
{
    return this->webView;
}

QWebEnginePage* WebContainer::getWebPage() const
{
    return this->webView ? this->webView->page() : nullptr;
}

void WebContainer::locationFocusRequested()
{
    this->locationEdit->setFocus();
    this->locationEdit->selectAll();
}
