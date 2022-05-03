#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "refreshthread.h"
#include "mqttsubscriberclient.h"
#include "dialogaddlocator.h"
#include "dialogmodifylocator.h"
#include "code_distance.h"

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:


    QList<QList<QString>> datalog;
    QString locatortopic[4] = {"silabs/aoa/angle/ble-pd-0C4314F02B3A","silabs/aoa/angle/ble-pd-0C4314EF5CEC","silabs/aoa/angle/ble-pd-0C4314EF67A4",""};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    refreshthread *thread;

    QGraphicsRectItem *rectangle;
    QGraphicsScene *scene;
    QList<QGraphicsEllipseItem> *locatordisplay;

    void setUrl(const QUrl &url); // ie ws://broker.hivemq.com:8000/mqtt
    void setTopic(const QString &topic);
    void setVersion(int v);
    void myMessageHandler();

public slots:
  void onNumberChanged(int i);

private slots:
    void on_pushButton_3_clicked();
    void on_listWidget_itemSelectionChanged();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient m_client;
    QMqttSubscription *m_subscription;
    QString m_topic;
    int m_version;
};
#endif // MAINWINDOW_H
