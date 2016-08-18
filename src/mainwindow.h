#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSharedMemory>
#include <QMutex>
#include <QAction>

#include <iostream>

#include "wifi.h"
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

private slots:
    void on_pushButton_clicked();
    void on_pushButton_name_clicked();
    void on_lineEdit_name_editingFinished();
    void on_pushButton_pwd_clicked();
    void on_lineEdit_pwd_editingFinished();
    void on_tabWidget_tabBarClicked(int index);
    void on_pushButton_save_clicked();
    void on_pushButton_reset_clicked();
    void on_actionAbout_triggered();
    void updateClients(QStringList);

private:
    Ui::MainWindow *ui;

    int m_mutex;

    Wifi wifi;
    WSettings m_wsettings;
    //WThread *_thread;

    QString path;
    QSystemTrayIcon* m_trayIcon;
    QAction* m_restoreAction;
    QAction* m_quitAction;
    QMenu* m_trayIconMenu;

    void createSystemTrayMenu(); //create customize menu
    void initUILanguageShow();
    void initUIValue();
    void setupTrayIcon();
    void setupSignalsSlots();
};

#endif // MAINWINDOW_H
