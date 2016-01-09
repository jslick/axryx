#include "mainwindow.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("abrowser");
    QApplication::setApplicationName("abrowser");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
