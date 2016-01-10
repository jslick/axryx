#include "webpage.h"
#include "tabhost.h"

WebPage::WebPage(TabHost* tabHost, QObject* parent) :
    QWebEnginePage(parent),
    tabHost(tabHost)
{

}

QWebEnginePage* WebPage::createWindow(QWebEnginePage::WebWindowType type)
{
    return this->tabHost ? this->tabHost->createTab() : QWebEnginePage::createWindow(type);
}
