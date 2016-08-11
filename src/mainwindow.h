#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QSharedMemory>
#include <QMutex>

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

    Wifi wifi;
    WSettings m_wsettings;
    QString path;

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

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon m_trayIcon;

    void createSystemTrayMenu(); //create customize menu
    void initUILanguageShow();
    void initUIValue();
    WThread *_thread;

    int m_mutex;

public slots:
    void updateClients(QStringList);

};

#endif // MAINWINDOW_H
