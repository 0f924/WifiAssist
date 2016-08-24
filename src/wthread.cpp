#include "wthread.h"

WThread::WThread():
    m_wdevices(new WDevices()),
    m_stop(false)
{
}

WThread::~WThread()
{
   this->~QThread();
}

void WThread::run()
{
    while(!m_stop)
    {
        emit clientChanged(m_wdevices->getDeviceList());
        sleep(5);
    }
    m_stop = false;
}

void WThread::stop()
{
    m_stop = true;
}
