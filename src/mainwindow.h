#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSharedMemory>
#include <QMutex>
#include <QAction>
#include <QCloseEvent>
#include <QStringList>
#include <QTranslator>

#include <iostream>

#include "wifi.h"
#include "device.h"
#include "wdevices.h"
#include "wsettings.h"
#include "about.h"
#include "wthread.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setMainWindowVisibility(bool state);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_name_clicked();
    void on_lineEdit_name_editingFinished();
    void on_pushButton_pwd_clicked();
    void on_lineEdit_pwd_editingFinished();
    void on_pushButton_save_clicked();
    void on_pushButton_reset_clicked();
    void on_actionAbout_triggered();
    void updateClients(QVector<Device *> device);

private:
    Ui::MainWindow *ui;

    int m_mutex;
    int m_information_count;

    Wifi *m_wifi;
    WSettings *m_wsettings;
    WDevices *m_wdevices;
    WThread *m_wthread;

    QTranslator *m_translator;
    QStringList m_languageList;
    QSystemTrayIcon* m_trayIcon;
    QAction* m_restoreAction;
    QAction* m_quitAction;
    QAction* m_controlWifi;
    QAction* m_restartWifi;
    QMenu* m_trayIconMenu;

    void createSystemTrayMenu(); //create customize menu
    void setupLanguage();
    void initUIValue();
    void setupTrayIcon();
    void setupSignalsSlots();
    QStringList findQmFiles();
    void setupLanguageOption();
    QString languageName(const QString &qmFile);
};

#endif // MAINWINDOW_H
