#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tabhost.h"

#include <QMainWindow>

class QTabWidget;

class MainWindow : public QMainWindow, public TabHost
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

    // TabHost
    QWebEnginePage* createTab();

protected:
    void closeEvent(QCloseEvent* event);

private slots:
    QWebEnginePage* addTab();

private:
    QTabWidget* webTabs = 0;
};

#endif // MAINWINDOW_H
