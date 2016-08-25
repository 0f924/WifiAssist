#include "wdevices.h"

#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include <QRegExp>


WDevices::WDevices()
{
}

QStringList WDevices::getDeviceListStr()
{

    //read ap.pid
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";
    QString client_list_filename = config_path+"/client.list";

    QStringList args = QStringList() << QCoreApplication::applicationDirPath()+"/bin/client.sh";
    QProcess qp;
    if(!qp.startDetached("bash",args))
    {
        QMessageBox::about(NULL,QT_TR_NOOP("Warning!"),QT_TR_NOOP("Can't Get Client List"));
    }
    qp.waitForFinished();


    QStringList client_list = QStringList();

    QFile inputFile(client_list_filename);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       if(!in.atEnd()) in.readLine();

       while (!in.atEnd())
       {
          QString line = in.readLine();
          client_list << line;
       }
       inputFile.close();
    }
    return client_list;
}

QVector<Device *> WDevices::getDeviceList(QStringList devicesListStr) const
{
    QVector<Device *> deviceList;
    //QStringList devicesListStr = getDeviceListStr();
    for(int i=0;i<devicesListStr.length();i++)
    {
        QString deviceStr = devicesListStr[i];
        QStringList deviceInfo = deviceStr.split(QRegExp("\\s+"));
        if(deviceInfo[2] == "*") continue;
        Device *device = new Device(deviceInfo[0],deviceInfo[1],deviceInfo[2]);
        deviceList.push_back(device);
    }
    return deviceList;
}

void WDevices::updateClients()
{
    m_newDeviceListStr.clear();
    m_leaveDeviceListStr.clear();
    m_newDeviceList.clear();
    m_leaveDeviceList.clear();

    QStringList currentDeviceListStr = getDeviceListStr();

    //get new clients
    for(int i=0;i<currentDeviceListStr.size();i++)
    {
        if(!m_oldClientsStr.contains(currentDeviceListStr[i]))
            m_newDeviceListStr.push_back(currentDeviceListStr[i]);
    }

    //get leave clients;
    for(int i=0;i<m_oldClientsStr.size();i++)
    {
        if(!currentDeviceListStr.contains(m_oldClientsStr[i]))
            m_leaveDeviceListStr.push_back(m_oldClientsStr[i]);
    }

    m_oldClientsStr = currentDeviceListStr;
}

QVector<Device *> WDevices::getNewDeviceList() const
{
    return getDeviceList(m_newDeviceListStr);
}

QVector<Device *> WDevices::getLeaveDeviceList() const
{
    return getDeviceList(m_leaveDeviceListStr);
}
