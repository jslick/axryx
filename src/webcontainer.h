#ifndef WEBCONTAINER_H
#define WEBCONTAINER_H

#include <QWidget>

class TabHost;

class QVBoxLayout;
class QLineEdit;
class QWebEngineView;
class QWebEnginePage;

class WebContainer : public QWidget
{
    Q_OBJECT
public:
    explicit WebContainer(TabHost* tabHost, QWidget* parent = 0);

    QWebEngineView* getWebView() const;

    QWebEnginePage* getWebPage() const;

signals:

public slots:
    void locationFocusRequested();

private:
    TabHost*        tabHost = 0;

    QVBoxLayout*    mainLayout = 0;
    QLineEdit*      locationEdit = 0;
    QWebEngineView* webView = 0;
};

#endif // WEBCONTAINER_H
