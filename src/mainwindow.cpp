#include "mainwindow.h"
#include "common.h"
#include "webcontainer.h"

#include <QAction>
#include <QSettings>
#include <QMenu>
#include <QTimer>
#include <QTabWidget>
#include <QToolButton>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      webTabs(new QTabWidget(this)),
      settingsMenu(new QMenu(tr("Settings"), this))
{
    this->setWindowIcon(QIcon(":/icons/axryx.png"));

    this->setCentralWidget(this->webTabs);

    // Actions
    QAction* newTabAction = new QAction(QIcon::fromTheme("tab-new"), tr("New tab"), this);
    newTabAction->setShortcut(tr("Ctrl+T"));
    connect(newTabAction, &QAction::triggered, this, &MainWindow::addTab);
    this->addAction(newTabAction);

    QAction* newWindowAction = new QAction(QIcon::fromTheme("window-new"), tr("New window"), this);
    newWindowAction->setShortcut(QKeySequence::New);
    connect(newWindowAction, &QAction::triggered, this, &MainWindow::createWindow);
    this->addAction(newWindowAction);

    // Settings Menu
    this->settingsMenu->addAction(newTabAction);
    this->settingsMenu->addAction(newWindowAction);

    this->webTabs->setTabsClosable(true);
    this->webTabs->setMovable(true);
    connect(this->webTabs, &QTabWidget::tabCloseRequested, [this](int index)
    {
        this->webTabs->removeTab(index);
        if (this->webTabs->count() == 0)
            this->addTab();
    });
    connect(this->webTabs, &QTabWidget::currentChanged, this, &MainWindow::updateWindowTitle);

    QToolButton* addTabButton = new QToolButton(this);
    addTabButton->setDefaultAction(newTabAction);
    this->webTabs->setCornerWidget(addTabButton, Qt::TopRightCorner);

    QAction* focusAddressAction = new QAction(tr("Focus location"), this);
    focusAddressAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(focusAddressAction, &QAction::triggered, [this]()
    {
        if (WebContainer* web = dynamic_cast<WebContainer*>(this->webTabs->currentWidget()))
            web->locationFocusRequested();
    });
    this->addAction(focusAddressAction);

    QSettings settings;
    restoreGeometry(settings.value("mainwindow/geometry").toByteArray());
    restoreState(settings.value("mainwindow/windowState").toByteArray());

    this->addTab();
    QTimer::singleShot(0, focusAddressAction, &QAction::trigger);
}

MainWindow::~MainWindow()
{

}

QWebEnginePage* MainWindow::createTab()
{
    return this->addTab(true);
}

QMenu* MainWindow::getSettingsMenu()
{
    return this->settingsMenu;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings;
    settings.setValue("mainwindow/geometry", saveGeometry());
    settings.setValue("mainwindow/windowState", saveState());
    QMainWindow::closeEvent(event);
}

QWebEnginePage* MainWindow::addTab(bool background)
{
    WebContainer* web = new WebContainer(this);
    this->webTabs->addTab(web, tr("New tab"));
    if (!background)
        this->webTabs->setCurrentWidget(web);
    connect(web->getWebView(), &QWebEngineView::titleChanged, [this,web](QString title)
    {
        if (title.length() > 50)
            title = tr("%1...").arg(title.left(47));

        int pos = this->webTabs->indexOf(web);
        if (pos >= 0)
        {
            this->webTabs->setTabText(pos, title);

            if (pos == this->webTabs->currentIndex())
                this->updateWindowTitle();
        }
    });

    return web->getWebPage();
}

void MainWindow::createWindow()
{
    MainWindow* newWindow = new MainWindow;
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    newWindow->show();
}

void MainWindow::updateWindowTitle()
{
    const int current = this->webTabs->currentIndex();
    if (current >= 0)
        this->setWindowTitle(this->webTabs->tabText(current) + " - " APP_NAME);
    else
        this->setWindowTitle(APP_NAME);
}
