#include "webcontainer.h"

#include <QRegularExpression>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QWebEngineView>
#include <QWebEngineProfile>

WebContainer::WebContainer(QWidget* parent)
    : QWidget(parent),
      mainLayout(new QVBoxLayout),
      locationEdit(new QLineEdit(this)),
      webView(new QWebEngineView(this))
{
    this->setLayout(this->mainLayout);

    QHBoxLayout* locationLayout = new QHBoxLayout;

    QPushButton* backButton = new QPushButton(QIcon::fromTheme("go-previous"), "", this);
    connect(backButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Back);
    });
    locationLayout->addWidget(backButton);

    QPushButton* forwardButton = new QPushButton(QIcon::fromTheme("go-next"), "", this);
    connect(forwardButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Forward);
    });
    locationLayout->addWidget(forwardButton);

    QPushButton* refreshButton = new QPushButton(QIcon::fromTheme("view-refresh"), "", this);
    connect(refreshButton, &QPushButton::clicked, [this]()
    {
        this->webView->triggerPageAction(QWebEnginePage::Reload);
    });
    locationLayout->addWidget(refreshButton);

    locationLayout->addWidget(this->locationEdit);
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
    });

    this->webView->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    this->mainLayout->addWidget(this->webView);
}

QWebEngineView* WebContainer::getWebView() const
{
    return this->webView;
}
