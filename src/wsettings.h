
#ifndef WSETTINGS_H
#define WSETTINGS_H
#include "QString"
#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QCoreApplication>
#include <QElapsedTimer>
/**
 * @brief The WSettings class
 *
 */
class WSettings
{
public:
    WSettings();
    WSettings(bool ifinit);
    ~WSettings();

    QSettings *m_settings;

    QString _path_exec;
    QString _APName;
    QString _Password;
    QString _Interface_Create;
    QString _Interface_Shared;
    QString _AccessPoint;
    QString _Language;



    QString path_exec() const;
    void setPath_exec(const QString &path_exec);
    QString APName() const;
    void setAPName(const QString &APName);
    QString Password() const;
    void setPassword(const QString &Password);
    QString Interface_Create() const;
    void setInterface_Create(const QString &Interface_Create);
    QString Interface_Shared() const;
    void setInterface_Shared(const QString &Interface_Shared);
    QString AccessPoint() const;
    void setAccessPoint(const QString &AccessPoint);
    QString Language() const;
    void setLanguage(const QString &Language);

    void setSettings(const QString &name,const QString &value);
    QString getSettings(const QString&name) const;

    void setConfigAttrName();

    void checkInterfaceListFile();
    void checkConfigFile();
    void setDefaultConfig();
    QStringList getInterfaceList();
    bool getAPStatus();
    QStringList getClientList();
};

#endif // WSETTINGS_H

