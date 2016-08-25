#include "wsettings.h"
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <iostream>

WSettings::WSettings():
    m_settings(new QSettings)
{        
       setConfigAttrName();
       checkInterfaceListFile();
       checkConfigFile();
}

WSettings::WSettings(bool needinit)
{
    if(!needinit)
        WSettings();
}

WSettings::~WSettings()
{
    delete this->m_settings;
}

void WSettings::setConfigAttrName()
{
    _path_exec = "PATH";
    _APName = "APNAME";
    _Password = "PASSWORD";
    _Interface_Create = "INTERFACE_CREATED";
    _Interface_Shared = "INTERFACE_SHARED";
    _AccessPoint = "ACCESSPOINT";
    _Language = "LANGUAGE";
}

void WSettings::setSettings(const QString &name,const QString &value)
{
    QString fullpath = "/settings/"+name;
    m_settings->setValue(fullpath,value);
}

QString WSettings::getSettings(const QString &name) const
{
    QString fullpath = "/settings/"+name;
    return m_settings->value(fullpath).toString();
}

QString WSettings::AccessPoint() const
{
    return this->getSettings(_AccessPoint);
}

void WSettings::setAccessPoint(const QString &AccessPoint)
{
    this->setSettings(_AccessPoint,AccessPoint);
}

QString WSettings::Interface_Shared() const
{
    return this->getSettings(_Interface_Shared);
}

void WSettings::setInterface_Shared(const QString &Interface_Shared)
{
   this->setSettings(_Interface_Shared,Interface_Shared);
}

QString WSettings::Interface_Create() const
{
    return this->getSettings(_Interface_Create);
}

void WSettings::setInterface_Create(const QString &Interface_Create)
{
    this->setSettings(_Interface_Create,Interface_Create);
}

QString WSettings::Password() const
{
    return this->getSettings(_Password);
}

void WSettings::setPassword(const QString &Password)
{
    this->setSettings(_Password,Password);
}

QString WSettings::APName() const
{
    return this->getSettings(_APName);
}

void WSettings::setAPName(const QString &APName)
{
    this->setSettings(_APName,APName);
}

QString WSettings::path_exec() const
{
    return this->getSettings(_path_exec);
}

void WSettings::setPath_exec(const QString &path_exec)
{
    this->setSettings(_path_exec,path_exec);
}

QString WSettings::Language() const
{
    return this->getSettings(_Language);
}

void WSettings::setLanguage(const QString &Language)
{
    this->setSettings(_Language,Language);
}


void WSettings::checkInterfaceListFile()
{
    //default config file "~/.WifiAssist/config.ini"
    //check is path exists
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";

    dir.setPath(config_path);
    //if not exist,mkdir and Then set default config file.
    if(!dir.exists())
    {
        dir.mkdir(config_path);
    }


    //run net.sh to get interface list
    QString interface_list_filename = config_path+"/interface.list";
    QFile file;
    file.setFileName(interface_list_filename);

    if(!file.exists())
    {
        QStringList args = QStringList() << QCoreApplication::applicationDirPath()+"/bin/net.sh";
        QProcess qp;
        if(!qp.startDetached("bash",args))
        {
            QMessageBox::about(NULL,QT_TR_NOOP("Warning!"),QT_TR_NOOP("Can't Get Interface List"));
        }

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<2000)
            QCoreApplication::processEvents();
    }

}


void WSettings::checkConfigFile()
{
    //default config file "~/.WifiAssist/config.ini"
    //check is path exists
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";
    QString filename = config_path+"/config.ini";
    dir.setPath(config_path);
    //if not exist,mkdir and Then set default config file.
    if(!dir.exists())
    {
        dir.mkdir(config_path);
    }
    QFile file;
    file.setFileName(filename);
    if(!file.exists())
    {

        m_settings = new QSettings(filename,QSettings::IniFormat);
        setDefaultConfig();
    }
    else
        m_settings = new QSettings(filename,QSettings::IniFormat);

    QString clientfile = config_path+"/client.list";
    QFile::remove(clientfile);
}

void WSettings::setDefaultConfig()
{
    this->setPassword("1234567890");
    this->setAccessPoint("192.168.12.1");
    this->setAPName("WifiAssistForLinux");

    QStringList interface_list = getInterfaceList();
    if(interface_list.contains("eth0"))
        this->setInterface_Shared("eth0");
    else
        this->setInterface_Shared(interface_list.at(0));

    if(interface_list.contains("wlan0"))
        this->setInterface_Create("wlan0");
    else
        this->setInterface_Create(interface_list.at(interface_list.size()-1));

    QString absolute_path = QCoreApplication::applicationDirPath()+"/bin/wifi.sh";
    this->setPath_exec(absolute_path);

    this->setLanguage("en_US");
}

QStringList WSettings::getInterfaceList()
{
    //read interface.list
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";
    QString interface_list_filename = config_path+"/interface.list";

    QStringList interface_list = QStringList();

    QFile inputFile(interface_list_filename);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          interface_list << line;
       }
       inputFile.close();
    }
    else
    {
        QMessageBox::warning(NULL,QT_TR_NOOP("Warning!"),QT_TR_NOOP("Can't find interface Record"));
    }
    return interface_list;
}

bool WSettings::getAPStatus()
{
    //read ap.pid
    QDir dir;
    QString config_path = dir.homePath()+"/.WifiAssist";
    QString ap_list_filename = config_path+"/ap.pid";

    QStringList ap_list = QStringList();

    QFile inputFile(ap_list_filename);
    if(inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          ap_list << line;
       }
       inputFile.close();
    }
    else
    {
        QMessageBox::warning(NULL,QT_TR_NOOP("Warning!"),QT_TR_NOOP("Can't find interface Record"));
    }
    if(ap_list.size() > 0)
        return true;
    return false;
}
