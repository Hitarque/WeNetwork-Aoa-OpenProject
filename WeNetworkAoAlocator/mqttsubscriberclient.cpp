#include "mqttsubscriberclient.h"
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>

mqttsubscriberclient:: mqttsubscriberclient()
{
}
mqttsubscriberclient:: ~mqttsubscriberclient()
{
}




void mqttsubscriberclient::setconnection(){
    m_client.setProtocolVersion(m_version == 3 ? QMqttClient::MQTT_3_1 : QMqttClient::MQTT_3_1_1);
    m_client.setHostname("localhost");
    m_client.setPort(1883);

    m_client.connectToHost();
    qDebug()<<m_client.state();
    qDebug()<<m_client.error();

    auto subscription = m_client.subscribe(QString("qtmqtt/topic1"));
    if (!subscription) {
        qDebug()<<"Error to sub";
    }
    else{
        qDebug()<<"Connected";
        connect(&m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
                const QString content = QDateTime::currentDateTime().toString()
                            + QLatin1String(" Received Topic: ")
                            + topic.name()
                            + QLatin1String(" Message: ")
                            + message
                            + QLatin1Char('\n');
                qDebug()<<content;
            });
    }
}
void mqttsubscriberclient::returndatafromtopics(){
    for(int i=0;i<datareceiv.size();i++)
    {
        qDebug()<<datareceiv.at(i);
    }

}

