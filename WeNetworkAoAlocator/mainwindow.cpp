#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "assetsdetected.h"


int set_selectedlocator;
int connectionbar=0;
int posx=0;
int posy=0;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread = new refreshthread(this);
    connect(thread,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));
    thread->start();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}


MainWindow::~MainWindow()
{
   // thread->Stop(true);
    thread->exit();
    thread->destroyed();
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
   Dialogaddlocator* dialog = new Dialogaddlocator();
   dialog->show();
}

void MainWindow::onNumberChanged(int i){
    //refresh display
    //reset all
    scene->clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();

    //set tools for frame
    QPen outlinePen(Qt::black);
    QBrush greenBrush(Qt::green);
    outlinePen.setWidth(2);
    rectangle = scene->addRect(0, 0, 152, 400, outlinePen);

    //Refresh list locators + display on frame
    if(database::GetInstance().returnlocatornumber()!=0){
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else{
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }

     for(int i=0;i<database::GetInstance().returnassetnumber();i++)
     {
         ui->listWidget_3->addItem("Asset :"+database::GetInstance().returnasset(i).name);
     }

    for(int i=0;i<database::GetInstance().returnlocatornumber();i++){
            Locator a = database::GetInstance().returnlocator(i);
            ui->listWidget->addItem(a.name + " IP: "+a.ip + " Locate in ("+QString::number(a.posx)+" M,"+QString::number(a.posy)+"M)");

            QGraphicsEllipseItem *b= scene->addEllipse(a.posx*20,a.posy*20,10,10,outlinePen);
               QGraphicsTextItem *c=scene->addText(a.name+"\n IP:"+a.ip, QFont("Arial", 10) );
               c->setPos(a.posx*20, a.posy*20);
               ui->listWidget_2->addItem(a.name + " IP: "+a.ip + " Locate in ("+QString::number(a.posx)+","+QString::number(a.posy)+")");
               for(int j=0;j<a.assetsdetecteds.length();j++){
                   ui->listWidget_2->addItem("     Asset: "+a.assetsdetecteds[j].name+" Azim:"+QString::number(a.assetsdetecteds[j].azim)+" Elev:"+QString::number(a.assetsdetecteds[0].elev)+"");
               }
    }

    //qDebug()<<m_client.state();
    if(m_client.state()== QMqttClient::Connecting)
    {
        connectionbar+=1;
        ui->progressBar->setValue(connectionbar);
        ui->label->setText("<font color='yellow'>try to connect</font>");
    }
    if(m_client.state()== QMqttClient::Connected)
    {
        connectionbar=0;
        ui->progressBar->setValue(100);
        ui->label->setText("<font color='green'>Connected</font>");
    }
    if(m_client.state()== QMqttClient::Disconnected)
    {
        connectionbar=0;
        ui->progressBar->setValue(connectionbar);
        ui->label->setText("<font color='red'>Disconnected</font>");
    }


    vector<vector<double>> data_locator= {
                                         {0,0,0},
                                         {0,0,0},
                                         {0,0,0},
                                         {0,0,0}
                                         };

    for(int i =0;i<database::GetInstance().returnlocatornumber();i++)
    {
        Locator locators = database::GetInstance().returnlocator(i);
            qDebug()<<locators.returnasset(0).name;
            data_locator[i][0]=locators.posx;
            data_locator[i][1]=locators.posy;
            data_locator[i][2]=locators.returnasset(0).azim;
            //data_locator[i][3]=a.returnasset(0).elev;

    }
    qDebug()<<"[Mainwindow.cpp]data_locator:"<<data_locator;
    if(data_locator[0][2]!=0 && data_locator[1][2]!=0){
            qDebug()<<"[Mainwindow.cpp]Print locator";
            Code_distance* codedistance= new Code_distance();
            vector<double> result= codedistance->asset_position(data_locator);
                    database::GetInstance().setnewposasset(database::GetInstance().returnlocator(0).returnasset(0).name,result[0],result[1]);
                    for(int i=0;i<database::GetInstance().returnassetnumber();i++){
                            Asset ass=database::GetInstance().returnasset(i);

                            QGraphicsEllipseItem *b= scene->addEllipse(ass.posx*20,ass.posy*20,10,10,outlinePen);
                               QGraphicsTextItem *c=scene->addText(ass.name+"\n X:"+QString::number(ass.posx)+"Y:"+QString::number(ass.posy), QFont("Arial", 10) );
                               c->setPos(ass.posx*20, ass.posy*20);

                               QDateTime dateTime = dateTime.currentDateTime();
                               datalog.append({dateTime.toString("yyyy-MM-dd HH:mm:ss"),QString::number(ass.posx),QString::number(ass.posy)});
                    }

        }


}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    set_selectedlocator= ui->listWidget->currentRow();
    database::GetInstance().sercurrentlocator(ui->listWidget->currentRow());
}


void MainWindow::on_pushButton_clicked()
{
    database::GetInstance().removelocator(set_selectedlocator);
    set_selectedlocator=0;
}


void MainWindow::on_pushButton_4_clicked()
{
            m_client.setProtocolVersion(m_version == 3 ? QMqttClient::MQTT_3_1 : QMqttClient::MQTT_3_1_1);
            m_client.setHostname("localhost");
            m_client.setPort(1883);

            m_client.connectToHost();
            qDebug()<<m_client.state();
            qDebug()<<m_client.error();
}


void MainWindow::on_pushButton_5_clicked()
{
    auto subscription = m_client.subscribe(QString("silabs/#"));
    if (!subscription) {
        qDebug()<<"[Mainwindow.cpp]Error to sub";
    }
    else{
        qDebug()<<"[Mainwindow.cpp]Connected";
        connect(&m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
                QString subStringaz = message.mid(12+2,9);
                qDebug()<<"[Mainwindow.cpp]Azimuth:  " +subStringaz;
                QString subStringelev = message.mid(37+2,9);
                qDebug()<<"[Mainwindow.cpp]Elevation:  " +subStringelev;

                if(database::GetInstance().findassets(topic.name().mid(37,20))!=NULL){
                         qDebug()<<"[Mainwindow.cpp]Asset find";
                         qDebug()<<"[Mainwindow.cpp]Asset :"+database::GetInstance().returnasset(0).name;

                }
                else{
                    database::GetInstance().addassets(topic.name().mid(37,20),0,0,"");
                    qDebug()<<"[Mainwindow.cpp]Asset added  ";
                }
                qDebug()<<topic.name();
                qDebug()<<message;
                    if( topic.name().indexOf(locatortopic[0]) >= 0){

                            database::GetInstance().modifylocatorassets(0,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                            qDebug()<<"[Mainwindow.cpp]Dataaded 0";

                    }
                    if( topic.name().indexOf(locatortopic[1]) >= 0){
                            database::GetInstance().modifylocatorassets(1,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                             qDebug()<<"[Mainwindow.cpp]Dataaded 1";
                    }
//                    if( topic.name().indexOf(locatortopic[2]) >= 0){
//                            database::GetInstance().modifylocatorassets(2,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
//                             qDebug()<<"[Mainwindow.cpp]Dataaded 2";
//                    }
//                    if( topic.name().indexOf(locatortopic[3]) >= 0){
//                            database::GetInstance().modifylocatorassets(3,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());

//                    }

            });


    }
}


void MainWindow::on_pushButton_6_clicked()
{
    m_client.publish(QString("qtmqtt/topic1"),"Hello toi");
}


void MainWindow::on_pushButton_2_clicked()
{
    Dialogmodifylocator* dialog = new Dialogmodifylocator();
    dialog->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    m_client.disconnectFromHost();
    qDebug()<<m_client.state();
    qDebug()<<m_client.error();
}

void MainWindow::myMessageHandler()
{

    QFile data("/logdata.csv");
    if (data.open(QFile::WriteOnly)) {
     QTextStream out(&data);

     for (int i = 0; i <+ datalog.length(); i++) {

             // Insert the data to file
             out << datalog[i][0] << ", "
                  << datalog[i][1] << ", "
                  << datalog[i][2] << ","
                  << "\n";
         }

     }
}





void MainWindow::on_pushButton_8_clicked()
{
    myMessageHandler();
    MainWindow().destroy();
}

