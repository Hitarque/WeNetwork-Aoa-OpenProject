#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "refreshthread.h"
#include "mqttsubscriberclient.h"
#include "dialogaddlocator.h"
#include "dialogmodifylocator.h"
#include "code_distance.h"
#include "dialoginfos.h"
#include "dialogoptions.h"

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
    QString locatortopic[4] = {"silabs/aoa/angle/ble-pd-0C4314F02B3A","silabs/aoa/angle/ble-pd-0C4314EF5CEC","silabs/aoa/angle/ble-pd-0C4314EF67A4","silabs/aoa/angle/ble-pd-0C4314EF67C4"};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    refreshthread *thread;

    QGraphicsRectItem *rectangle;
    QGraphicsScene *scene;
    QList<QGraphicsEllipseItem> *locatordisplay;

    void setUrl(const QUrl &url);
    void setTopic(const QString &topic);
    void setVersion(int v);
    void myMessageHandler();
    void myMessageHandler1();

    QMenuBar * createMenus();

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

    void on_action_Options_triggered();

    void on_action_info_triggered();

    void on_action_Fermer_triggered();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    QMqttClient m_client;
    QMqttSubscription *m_subscription;
    QString m_topic;
    int m_version;
};
#endif // MAINWINDOW_H
