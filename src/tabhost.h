#pragma once

class QWebEnginePage;

class TabHost
{
public:
    virtual QWebEnginePage* createTab() = 0;
};
