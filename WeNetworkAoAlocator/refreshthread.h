#ifndef REFRESHTHREAD_H
#define REFRESHTHREAD_H

#include <QThread>

class refreshthread : public QThread
{
    Q_OBJECT
public:
    explicit refreshthread(QObject *parent = nullptr);
    void run();
    bool Stop =false;
signals:
    void NumberChanged(int);

public slots:
};

#endif // REFRESHTHREAD_H
