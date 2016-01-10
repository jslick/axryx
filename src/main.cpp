#include "mainwindow.h"
#include "common.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName(APP_NAME);
    QApplication::setApplicationName(APP_NAME);

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

    return a.exec();
}
