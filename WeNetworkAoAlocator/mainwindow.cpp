/*Fait par Hugo FABRE*/
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "assetsdetected.h"
#include "jsonparser.h"

int set_selectedlocator;
int connectionbar=0;
int posx=0;
int posy=0;


/*initialisation de la mainwindow, on y crée le thread qui metteras a jour la page automatiquement, on y définit aussi la scéne dans la graphics view afin*
de permettre l'affichage en 2D
C'est ici aussi que le json de config s'ouvre et s'enregistre pour la session
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    jsonparser* js= new jsonparser();
    js->jsonloader();
    //qDebug()<<"[Mainwindows.cpp]Loading mainwindow";
    ui->setupUi(this);
    //qDebug()<<"[Mainwindows.cpp]Setup";

    thread = new refreshthread(this);
    connect(thread,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));
    thread->start();
    //qDebug()<<"[Mainwindows.cpp]Thread lunch";
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //qDebug()<<"[Mainwindows.cpp]Graphicview loaded";
    //qDebug()<<"[Mainwindows.cpp]mainwindow loaded";
}

/*Destructeur de la mainwindows et du thread de maj*/
MainWindow::~MainWindow()
{
   // thread->Stop(true);
    thread->exit();
    thread->destroyed();
    delete ui;
}

/*Ouvre le dialog de création de locator*/
void MainWindow::on_pushButton_3_clicked()
{
   Dialogaddlocator* dialog = new Dialogaddlocator();
   dialog->show();
}

/*Mise a jour de l'affichage de la mainwindows*/
void MainWindow::onNumberChanged(int i){
    //qDebug()<<"[Mainwindows.cpp]looper";


    //reset les list widget d'affichage des données de locator, locator/asset et Asset
    scene->clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();

    //Nous définisson les tools qui nous servirons pour l'affichage dans la Qgraphicscene
    QPen outlinePen(Qt::black);
    QBrush greenBrush(Qt::green);
    outlinePen.setWidth(2);
    //rectangle = scene->addRect(0, 0, 152, 400, outlinePen);

    /*On definit l'affichage du plan en dessous de l'affichage*/
    scene->addPixmap(QPixmap(database::GetInstance().urlAoa_locaor+"/plan2.svg"));

    //Mise a jour de la liste des locators  et activation ou non des boutons associé
    if(database::GetInstance().returnlocatornumber()!=0){
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else{
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }

    /*Affichage de la liste des asset + leur localisation en X et Y*/
     for(int i=0;i<database::GetInstance().returnassetnumber();i++)
     {
         ui->listWidget_3->addItem("Asset :"+database::GetInstance().returnasset(i).name+" X:"+QString::number(database::GetInstance().returnasset(i).posx)+" Y:"+QString::number(database::GetInstance().returnasset(i).posy));
     }

    /*Affichage dans la qgraphicscene de nos locators + ajout dans les listes latérales*/
    for(int i=0;i<database::GetInstance().returnlocatornumber();i++){
            Locator a = database::GetInstance().returnlocator(i);
            ui->listWidget->addItem(a.name + " IP: "+a.ip + " Locate in ("+QString::number(a.posx)+" M,"+QString::number(a.posy)+"M)");
            QGraphicsEllipseItem *b= scene->addEllipse(a.posx*20,a.posy*20,10,10,outlinePen);
               QGraphicsTextItem *c=scene->addText(a.name+"\n IP:"+a.ip, QFont("Arial", 10) );
               c->setPos(a.posx*20, a.posy*20);
               ui->listWidget_2->addItem(a.name + " IP: "+a.ip + " Locate in ("+QString::number(a.posx)+","+QString::number(a.posy)+")");
               for(int j=0;j<a.assetsdetecteds.length();j++){
                   ui->listWidget_2->addItem("     Asset: "+a.assetsdetecteds[j].name+" Azim:"+QString::number(a.assetsdetecteds[j].azim)+" Elev:"+QString::number(a.assetsdetecteds[0].elev)+"");
                   //qDebug()<<j<<"     Asset: "<<a.assetsdetecteds[j].name<<" Azim:"<<QString::number(a.assetsdetecteds[j].azim)<<" Elev:"<<QString::number(a.assetsdetecteds[0].elev);
               }

    }

    /*affichage de la connection au broker*/
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

    /*Lancement des calculs de positions par assets detecté, cette partie fait les calculs, met en mémoire et s'occupe de l'affichage
    /!\Ligne 154 on définit en "dur" le nom de l'asset a pendre en compte!
    */
    vector<vector<double>> data_locator= {
                                         {0,0,0},
                                         {0,0,0},
                                         {0,0,0},
                                         {0,0,0}
                                         };
    int nombrededatainmemory=0;
    for(int i =0;i<database::GetInstance().returnlocatornumber();i++)
    {
        Locator locators = database::GetInstance().returnlocator(i);
            ////qDebug()<<locators.returnasset(0).name;
            data_locator[i][0]=locators.posx;
            data_locator[i][1]=locators.posy;
            data_locator[i][2]=locators.returnasset(0).azim;
            QDateTime dateTime = dateTime.currentDateTime();
            nombrededatainmemory=i;

    }
    //qDebug()<<"[Mainwindow.cpp]data_locator:"<<data_locator;
    if(data_locator[0][2]!=0 && data_locator[1][2]!=0){
            //qDebug()<<"[Mainwindow.cpp]Print locator";
            Code_distance* codedistance= new Code_distance();
            vector<double> result= codedistance->asset_position(data_locator);
            //qDebug()<<result[0]<<"  "<<result[1];
                    //database::GetInstance().setnewposasset(database::GetInstance().returnlocator(0).returnasset(0).name,result[0],result[1]);

                    database::GetInstance().setnewposasset("ble-pd-588E81440971",result[0],result[1]);

                    //qDebug()<<"[Mainwindow.cpp]Displaying new asset position calculresult "<<result[0]<<"  "<<result[1];
                    for(int i=0;i<1;i++){
                            Asset ass=database::GetInstance().returnasset(i);
                            //qDebug()<<"[Mainwindow.cpp]Displaying new asset position  "<<ass.posx*20<<"  "<<ass.posy*20;
                            QGraphicsEllipseItem *b= scene->addEllipse(ass.posx*20,ass.posy*20,10,10,outlinePen);
                            QGraphicsTextItem *c=scene->addText(ass.name+"\n X:"+QString::number(ass.posx)+"Y:"+QString::number(ass.posy), QFont("Arial", 10) );
                            c->setPos(ass.posx*20, ass.posy*20);

                               QDateTime dateTime = dateTime.currentDateTime();
                               QString azlocators;
                               for(int i=0;i<=nombrededatainmemory;i++){
                                   azlocators=azlocators+","+QString::number(data_locator[i][2]);
                               }
                               //qDebug()<<dateTime.toString("yyyy-MM-dd HH:mm:ss")+"|"+ QString::number(ass.posx)+"|"+ QString::number(ass.posy) +"|"+ azlocators;
                               datalog.append({dateTime.toString("yyyy-MM-dd HH:mm:ss"),QString::number(ass.posx),QString::number(ass.posy),azlocators});
                    }

}}

/*Permet de définir la selection dans la listwidget afin de pouvoir modifier ou supprimer*/
void MainWindow::on_listWidget_itemSelectionChanged()
{
    //qDebug()<<"[Mainwindows.cpp]itemselectedchanged";
    set_selectedlocator= ui->listWidget->currentRow();
    database::GetInstance().sercurrentlocator(ui->listWidget->currentRow());
}


/*Destruction d'un locator selectionné si appuie sur le bouton*/
void MainWindow::on_pushButton_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Removinglocator";
    database::GetInstance().removelocator(set_selectedlocator);
    set_selectedlocator=0;
}

/*Connection au broker MQTT
/!\LE FICHIER DE CONFIGURATION NE FONCTIONNE PAS ENCORE SUR CETTE PARTIE PROBLEME DE CONVERTION STRING->INT->QINT
*/
void MainWindow::on_pushButton_4_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Mqtt linking";
            m_client.setProtocolVersion(m_version == 3 ? QMqttClient::MQTT_3_1 : QMqttClient::MQTT_3_1_1);
            //m_client.setHostname(database::GetInstance().returnurlbroker());
            m_client.setHostname("localhost");

            //m_client.setPort((qint16)(database::GetInstance().returnportbroker()).toInt());
            m_client.setPort(1883);

            m_client.connectToHost();
            //qDebug()<<m_client.state();
            //qDebug()<<m_client.error();
}

/*subscribing aux topics demandé a l'appuie sur le bouton
/!\ICI LE NOMBRE DE LOCATOR A CONECTE A SON IMPORTANCE COMMENTER LES IF EN FONCTION DU NOMBRE DE LOCATOR NECESSAIRE, MAINWINDOWS.H->CORRIGER LES NOM DE TOPICS DANS LE BONNE ORDRE
*/
void MainWindow::on_pushButton_5_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Subscribing MQTT";
    auto subscription = m_client.subscribe(QString("silabs/#"));
    if (!subscription) {
        //qDebug()<<"[Mainwindow.cpp]Error to sub";
    }
    else{
        //qDebug()<<"[Mainwindow.cpp]Connected";
        connect(&m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
                QString subStringaz = message.mid(12+2,9);
                //qDebug()<<"[Mainwindow.cpp]Azimuth:  " +subStringaz;
                QString subStringelev = message.mid(37+2,9);
                //qDebug()<<"[Mainwindow.cpp]Elevation:  " +subStringelev;

                if(database::GetInstance().findassets(topic.name().mid(37,20))!=NULL){
                         //qDebug()<<"[Mainwindow.cpp]Asset find";
                         //qDebug()<<"[Mainwindow.cpp]Asset :"+database::GetInstance().returnasset(0).name;

                }
                else{
                    database::GetInstance().addassets(topic.name().mid(37,20),0,0,"");
                    //qDebug()<<"[Mainwindow.cpp]Asset added  "<<topic.name().mid(37,20);
                }
                //qDebug()<<topic.name();
                //qDebug()<<message;

                    if( topic.name().indexOf(locatortopic[0]) >= 0){
                          //  if(littlebdd.contains("Locator 1")){
                                database::GetInstance().modifylocatorassets(0,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                                //qDebug()<<"[Mainwindow.cpp]Dataaded 0";
                         //   }

                    }
                    if( topic.name().indexOf(locatortopic[1]) >= 0){
                       // if(littlebdd.contains("Locator 2")){
                            database::GetInstance().modifylocatorassets(1,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                             //qDebug()<<"[Mainwindow.cpp]Dataaded 1";
                     //   }
                    }
                    if( topic.name().indexOf(locatortopic[2]) >= 0){
                        //if(littlebdd.contains("Locator 3")){
                            database::GetInstance().modifylocatorassets(2,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                             //qDebug()<<"[Mainwindow.cpp]Dataaded 2";
                        //}
                    }
                    if( topic.name().indexOf(locatortopic[3]) >= 0){
                        //if(littlebdd.contains("Locator 4")){
                            database::GetInstance().modifylocatorassets(3,topic.name().mid(37,20),"",subStringaz.toDouble(),subStringelev.toDouble());
                            //qDebug()<<"[Mainwindow.cpp]Dataaded 3";
                       // }
                    }

            });


    }
}

/*Test d'envois de message au Broker mqtt*/
void MainWindow::on_pushButton_6_clicked()
{
    ////qDebug()<<"[Mainwindows.cpp]test mqtt";
    //m_client.publish(QString("qtmqtt/topic1"),"Hello toi");
}

/*Ouverture du dialog de modification du locator selectionne*/
void MainWindow::on_pushButton_2_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Modifing locator";
    Dialogmodifylocator* dialog = new Dialogmodifylocator();
    dialog->show();
}

/*Deconnection au broker MQTT*/
void MainWindow::on_pushButton_7_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Mqtt diconnected";
    m_client.disconnectFromHost();
    //qDebug()<<m_client.state();
    //qDebug()<<m_client.error();
}

/*Mise ne mémoire des logs*/
void MainWindow::myMessageHandler()
{
    QDateTime dateTime = dateTime.currentDateTime();
    QFile data(database::GetInstance().returnurllogdata()+"logdata_"+dateTime.toString("yyyy-MM-dd-HH-mm-ss")+".csv");
    if (data.open(QFile::WriteOnly)) {
     QTextStream out(&data);

     for (int i = 0; i <+ datalog.length(); i++) {

             // Insert the data to file
             out << datalog[i][0] << ", "
                  << datalog[i][1] << ", "
                  << datalog[i][2] << ","
                  << datalog[i][3] << ","
                  << "\n";
         }

     }
    datalog.clear();
}


/*Fermetre a l'appuie + maj du json d'options + Création du fichier de log*/
void MainWindow::on_pushButton_8_clicked()
{
    //qDebug()<<"[Mainwindows.cpp]Closing Mainwindows and app";
    myMessageHandler();
    jsonparser* js= new jsonparser();
    js->jsonsaver();
    MainWindow().destroy();
}

/*Affichage du dialog d'options*/
void MainWindow::on_action_Options_triggered()
{
    Dialogoptions* dialog = new Dialogoptions();
    dialog->show();
}

/*Affichage du dialog d'infos*/
void MainWindow::on_action_info_triggered()
{
    Dialoginfos* dialog = new Dialoginfos();
    dialog->show();
}

/*Bouton savec in csv ->sauvegarde dans un csv*/
void MainWindow::on_action_Fermer_triggered()
{
    //qDebug()<<"[Mainwindows.cpp]Closing Mainwindows and app";
    myMessageHandler();
    jsonparser* js= new jsonparser();
    js->jsonsaver();
    MainWindow().destroy();
}

/*Nothing*/
void MainWindow::on_pushButton_10_clicked()
{
   //debut test positio
}
/*Nothing*/
void MainWindow::on_pushButton_9_clicked()
{
    //fin test position
    myMessageHandler();
}

