#ifndef WTHREAD_H
#define WTHREAD_H
#include <QThread>
#include <QVector>

#include "device.h"
#include "wdevices.h"

class WThread : public QThread
{
    Q_OBJECT

public:
    WThread();
    ~WThread();
    void stop();

private:
    WDevices *m_wdevices;
    bool m_stop;

signals:
    void clientChanged(QVector<Device *> devices);

protected:
    void run();
};

#endif // WTHREAD_H
