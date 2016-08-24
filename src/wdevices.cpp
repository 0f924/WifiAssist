#include "wdevices.h"

#include <QString>
#include <QStringList>
#include <QProcess>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>


WDevices::WDevices()
{

}

QStringList WDevices::getDeviceListStr()
{

    QStringList args = QStringList() << QCoreApplication::applicationDirPath()+"/bin/client.sh";
    QProcess qp;
    if(!qp.startDetached("bash",args))
    {
        QMessageBox::about(NULL,QT_TR_NOOP("Warning!"),QT_TR_NOOP("Can't Get Client List"));
    }
    qp.waitForFinished();

    //read ap.pid
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";
    QString client_list_filename = config_path+"/client.list";

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

QVector<Device *> WDevices::getDeviceList()
{
    QVector<Device *> deviceList;
    QStringList devicesListStr = getDeviceListStr();
    for(int i=0;i<devicesListStr.length();i++)
    {
        QString deviceStr = devicesListStr[i];
        QStringList deviceInfo = deviceStr.split(" ");
        Device *device = new Device(deviceInfo[0],deviceInfo[1],deviceInfo[2]);
        deviceList.push_back(device);
    }
    return deviceList;
}
