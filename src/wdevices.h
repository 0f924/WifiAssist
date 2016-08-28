#ifndef WDEVICES_H
#define WDEVICES_H
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QVector>
#include <QStringList>
#include <QMap>

#include "device.h"

class WDevices
{
public:
    WDevices();
    QVector<Device *> getDeviceList(QStringList devicesListStr) const;
    void updateClients();

    QVector<Device *> getNewDeviceList() const;
    QVector<Device *> getLeaveDeviceList() const;
    QVector<Device *> getUpdateDeviceList() const;
    QString getDeviceLogoName(QString &deviceMac);

private:
    QStringList m_oldClientsStr;
    QVector<Device *> m_oldClients;
    QStringList m_newDeviceListStr;
    QVector<Device *> m_newDeviceList;
    QStringList m_leaveDeviceListStr;
    QVector<Device *> m_leaveDeviceList;
    QStringList getDeviceListStr();
    QMap<QString,QString> m_macinfo;
    void loadMacInfo();

};

#endif // WDEVICES_H
