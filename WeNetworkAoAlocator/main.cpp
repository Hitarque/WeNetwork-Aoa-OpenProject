/*Fait par Hugo FABRE*/
#include "mainwindow.h"
#include "mqttsubscriberclient.h"
#include <QApplication>
#include <QThread>
#include <QPluginLoader>

/*Lancement du programme*/
int main(int argc, char *argv[])
{
    qDebug()<<"Run";
    QApplication a(argc, argv);
    MainWindow w;
    database::GetInstance().linebyline("E:/logdata.csv");
    w.show();
    return a.exec();
}


