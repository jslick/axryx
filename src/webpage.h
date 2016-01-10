#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>

class TabHost;

class WebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit WebPage(TabHost* tabHost, QObject *parent = 0);

signals:

public slots:

protected:
    QWebEnginePage* createWindow(WebWindowType type);

private:
    TabHost* tabHost = 0;
};

#endif // WEBPAGE_H
