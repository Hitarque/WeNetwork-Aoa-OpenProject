#include "refreshthread.h"
#include <QtCore>
refreshthread::refreshthread(QObject *parent)
    : QThread{parent}
{

}

void refreshthread::run()
{
    while(true)
      {
        QMutex mutex;
        mutex.lock();
        if(this->Stop){break;}
        mutex.unlock();

        emit NumberChanged(1);
        this->msleep(100);

    }
}
