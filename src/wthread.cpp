#include "wthread.h"

WThread::WThread()
{
    _settings = new WSettings(false);
}

WThread::~WThread()
{
   delete this->_settings;
   this->~QThread();
}

void WThread::run()
{
    //keep refresh ap status and client list;
    if(_settings!=NULL && _settings->getAPStatus())
    {
        emit updateUI(_settings->getClientList());
    }
}

