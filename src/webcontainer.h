#ifndef WEBCONTAINER_H
#define WEBCONTAINER_H

#include <QWidget>

class QVBoxLayout;
class QLineEdit;
class QWebEngineView;

class WebContainer : public QWidget
{
    Q_OBJECT
public:
    explicit WebContainer(QWidget* parent = 0);

    QWebEngineView* getWebView() const;

signals:

public slots:
    void locationFocusRequested();

private:
    QVBoxLayout*    mainLayout = 0;
    QLineEdit*      locationEdit = 0;
    QWebEngineView* webView = 0;
};

#endif // WEBCONTAINER_H
