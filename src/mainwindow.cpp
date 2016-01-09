#include "mainwindow.h"
#include "webcontainer.h"

#include <QTabWidget>
#include <QToolButton>
#include <QWebEngineView>
#include <QSettings>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      webTabs(new QTabWidget(this))
{
    this->setWindowIcon(QIcon::fromTheme("internet-web-browser"));

    this->setCentralWidget(this->webTabs);

    this->webTabs->setTabsClosable(true);
    this->webTabs->setMovable(true);
    connect(this->webTabs, &QTabWidget::tabCloseRequested, this->webTabs, &QTabWidget::removeTab);

    QToolButton* addTabButton = new QToolButton(this);
    addTabButton->setIcon(QIcon::fromTheme("tab-new"));
    addTabButton->setShortcut(QKeySequence::AddTab);
    this->webTabs->setCornerWidget(addTabButton, Qt::TopRightCorner);
    connect(addTabButton, SIGNAL(clicked()), SLOT(addTab()));

    QSettings settings;
    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    restoreState(settings.value("mainwindow/windowState").toByteArray());

    this->addTab();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings;
    settings.setValue("mainwindow/geometry", saveGeometry());
    settings.setValue("mainwindow/windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::addTab()
{
    WebContainer* web = new WebContainer(this);
    this->webTabs->addTab(web, tr("New tab"));
    this->webTabs->setCurrentWidget(web);
    connect(web->getWebView(), &QWebEngineView::titleChanged, [this,web](QString title)
    {
        if (title.length() > 50)
            title = tr("%1...").arg(title.left(47));

        int pos = this->webTabs->indexOf(web);
        if (pos >= 0)
            this->webTabs->setTabText(pos, title);
    });
}
