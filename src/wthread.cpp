#include "wthread.h"
#include <iostream>

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
        sleep(1);
        //std::cout<<"running..."<<std::endl;

        m_wdevices->updateClients();
        QVector<Device *> update_devices = m_wdevices->getUpdateDeviceList();
        QVector<Device *> new_devices = m_wdevices->getNewDeviceList();
        QVector<Device *> leave_devices = m_wdevices->getLeaveDeviceList();

        if(!(new_devices.size()==0 && leave_devices.size()==0))
            emit clientUpdate(update_devices);
        if(new_devices.size() > 0)
            emit clientAdd(new_devices);
        if(leave_devices.size() > 0)
            emit clientLeave(leave_devices);
    }
    m_stop = false;
}

void WThread::stop()
{
    m_stop = true;
}
