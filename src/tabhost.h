#pragma once

class QWebEnginePage;
class QMenu;

class TabHost
{
public:
    virtual QWebEnginePage* createTab() = 0;

    virtual QMenu* getSettingsMenu() = 0;

    virtual ~TabHost() {}
};
