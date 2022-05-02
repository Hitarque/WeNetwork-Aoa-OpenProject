#ifndef MQTTSUBSCRIBERCLIENT_H
#define MQTTSUBSCRIBERCLIENT_H

#include <QtCore/QObject>
#include <QtMqtt/qmqttclient.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QLoggingCategory>
#include <QtWidgets/QMessageBox>
#include <QList>
class mqttsubscriberclient : public QDialog
{
     Q_OBJECT
public:
    mqttsubscriberclient();
    ~mqttsubscriberclient();

    void setconnection();
    void returndatafromtopics();
    QList<QString> datareceiv;
public slots:

private:
    QMqttClient m_client;
    QString m_topic;
    int m_version;
};

#endif // MQTTSUBSCRIBERCLIENT_H
