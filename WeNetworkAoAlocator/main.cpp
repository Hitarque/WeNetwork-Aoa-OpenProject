#include "mainwindow.h"
#include "mqttsubscriberclient.h"
#include <QApplication>
#include <QThread>
#include <QPluginLoader>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}


