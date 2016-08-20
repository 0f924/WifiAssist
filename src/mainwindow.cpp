#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <src/wsettings.h>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mutex(0),
    m_trayIcon(new QSystemTrayIcon(this)),
    m_restoreAction(new QAction(tr("&Hide WifiAssist"), this)),
    m_quitAction(new QAction(tr("&Quit"), this)),
    m_trayIconMenu(new QMenu(this))
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->removeTab(1);

    initUIValue();
    initUILanguageShow();

    setupTrayIcon();
    setupSignalsSlots();
}

MainWindow::~MainWindow()
{
    wifi.stopWifi();
    delete ui;
}

void MainWindow::setupSignalsSlots()
{
    //signal-slot:
    //connect(_thread,SIGNAL(updateUI(QStringList)),this,SLOT(updateClients(QStringList)),Qt::QueuedConnection);

    connect(m_restoreAction, &QAction::triggered, this, [this](){
        setMainWindowVisibility(isHidden()
                                || windowState() == Qt::WindowMinimized
                                || (qApp->applicationState() == Qt::ApplicationInactive));
    });
    connect(m_quitAction, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::setMainWindowVisibility(bool state)
{
    if(state){
        showNormal();
        setWindowState(Qt::WindowNoState);
        qApp->processEvents();
        setWindowState(Qt::WindowActive);
        qApp->processEvents();
        qApp->setActiveWindow(this);
        qApp->processEvents();
        m_restoreAction->setText(tr("&Hide WifiAssist"));
    }else{
        m_restoreAction->setText(tr("&Show WifiAssist"));
        hide();
    }
}


void MainWindow::initUIValue()
{
    ui->lineEdit_name->setText(m_wsettings.APName());

    ui->lineEdit_pwd ->setText(m_wsettings.Password());

    ui->lineEdit_ap->setText(m_wsettings.AccessPoint());


   /* QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)");
    QRegExpValidator *v = new QRegExpValidator(ipRx,this);
    ui->lineEdit_ap->setValidator(v);
    ui->lineEdit_ap->setInputMask("000.000.000.000;\ ");*/


    //get interface list
    QStringList interface_list = m_wsettings.getInterfaceList();

    ui->comboBox_createdinterface->clear();
    ui->comboBox_createdinterface->addItems(interface_list);
    ui->comboBox_createdinterface->setCurrentText(m_wsettings.Interface_Create());

    ui->comboBox_shareinterface->clear();
    ui->comboBox_shareinterface->addItems(interface_list);
    ui->comboBox_shareinterface->setCurrentText(m_wsettings.Interface_Shared());

    QStringList language_list  = QStringList() << "English" << "简体中文";
    ui->comboBox_language->clear();
    ui->comboBox_language->addItems(language_list);

    ui->label_tip->setHidden(true);

}

void MainWindow::initUILanguageShow()
{
    //default language:zh_CN
    if(m_wsettings.Language() == "zh_CN")
    {
        ui->label_ap->setText("接入点");
        ui->label_name->setText("名称");
        ui->label_pwd->setText("密码");
        ui->label_shareinterface->setText("共享网卡");
        ui->label_createdinterface->setText("热点网卡");
        ui->label_language->setText("语言");
        ui->comboBox_language->setCurrentIndex(1);
    }
    else if(m_wsettings.Language() == "en_US")
    {
        ui->label_ap->setText("AccessPoint");
        ui->label_name->setText("WifiName");
        ui->label_pwd->setText("Password");
        ui->label_shareinterface->setText("SharedInterface");
        ui->label_createdinterface->setText("APInterface");
        ui->label_language->setText("Language");
        ui->comboBox_language->setCurrentIndex(0);
    }
}

void MainWindow::setupTrayIcon()
{
    //Check if System Support SystemTrayIcon.
    //Linux:X11
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        m_trayIconMenu->addAction(m_restoreAction);
        m_trayIconMenu->addSeparator();
        m_trayIconMenu->addAction(m_quitAction);

        m_trayIcon->setIcon(QIcon(":img/WifiAssist.ico"));
        m_trayIcon->setContextMenu(m_trayIconMenu);
        m_trayIcon->show();
     }
}

void MainWindow::on_pushButton_clicked()
{

    QString text = ui->pushButton->text();
    if(QString::compare(text,"START") == 0)
    {
        if(wifi.startWifi())
            ui->pushButton->setText("STOP");
    }
    else if(QString::compare(text,"STOP") == 0)
    {
        if(wifi.stopWifi())
            ui->pushButton->setText("START");
    }
    else
    {
        QMessageBox::warning(NULL,"Error","Wrong!");
    }
}

void MainWindow::on_pushButton_name_clicked()
{
    ui->lineEdit_name->setEnabled(true);
}

void MainWindow::on_lineEdit_name_editingFinished()
{

    if(m_mutex == 0)
    {
        m_mutex = 1;
        return;
    }
    else
    {
        m_mutex = 0;
        ui->lineEdit_name->setEnabled(false);
        //if config not changed,return
        if(ui->lineEdit_name->text() == m_wsettings.APName())
            return;

        ui->lineEdit_name->setEnabled(false);
        m_wsettings.setAPName(ui->lineEdit_name->text());

        //add apply tips
        ui->label_tip->setHidden(false);
        ui->label_tip->setText("Apply WifiName Success!");

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<3000)
            QCoreApplication::processEvents();
        ui->label_tip->setHidden(true);


        if(QString::compare(ui->pushButton->text(),"STOP") == 0)
        {
            ui->pushButton->setText("Restaring...");
            wifi.restartWifi();
            ui->pushButton->setText("STOP");
        }
    }

}

void MainWindow::on_pushButton_pwd_clicked()
{
    ui->lineEdit_pwd->setEnabled(true);
}

void MainWindow::on_lineEdit_pwd_editingFinished()
{

    if(m_mutex == 0)
    {
        m_mutex = 1;
        return;
    }
    else
    {
        m_mutex = 0;
        ui->lineEdit_pwd->setEnabled(false);
        if(ui->lineEdit_pwd->text() == m_wsettings.Password())
            return;
        if(ui->lineEdit_pwd->text().size() < 8)
            QMessageBox::information(this,"Settings","Password Should More Than 8 Characters!",QMessageBox::Warning);

        ui->lineEdit_pwd->setEnabled(false);
        m_wsettings.setPassword(ui->lineEdit_pwd->text());

        //add apply tips
        ui->label_tip->setHidden(false);
        ui->label_tip->setText("Apply Password Success!");

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<3000)
            QCoreApplication::processEvents();
        ui->label_tip->setHidden(true);

        if(QString::compare(ui->pushButton->text(),"STOP") == 0)
        {
            ui->pushButton->setText("Restaring...");
            wifi.restartWifi();
            ui->pushButton->setText("STOP");
        }
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    QString apoint = this->ui->lineEdit_ap->text();
    QString interface_created = this->ui->comboBox_createdinterface->currentText();
    QString interface_shared = this->ui->comboBox_shareinterface->currentText();
    if(apoint.size() == 0)
    {
        QMessageBox::information(this,"Settings","Access Point Can't Be Empty!",QMessageBox::Ok);
        return;
    }
    if(interface_created.size() == 0)
    {
        QMessageBox::information(this,"settings","Wifi Interface Can't Be Empty!",QMessageBox::Ok);
        return;
    }
    if(interface_shared.size() == 0)
    {
        QMessageBox::information(this,"settings","Shared Interface Can't Be Empty!",QMessageBox::Ok);
        return;
    }

    if(!interface_created.startsWith("wl"))
    {
        QMessageBox::StandardButton stdbtn = QMessageBox::warning(NULL,"Settings",
                                 "This Wifi Interface May not work,Still Use it?",
                                 QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(stdbtn == QMessageBox::No)
            return;
    }
    if(!(interface_shared.contains("eth") || interface_shared.contains("en")) || interface_shared.contains("wl"))
    {
        QMessageBox::StandardButton stdbtn = QMessageBox::warning(NULL,"Settings",
                                "This Shared Interface May not work,Still Use it?",
                                QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(stdbtn == QMessageBox::No)
            return;
    }

    m_wsettings.setAccessPoint(apoint);
    m_wsettings.setInterface_Create(interface_created);
    m_wsettings.setInterface_Shared(interface_shared);

    //save language config
    switch (ui->comboBox_language->currentIndex())
    {
    case 0:
         m_wsettings.setLanguage("en_US");break;
    case 1:
         m_wsettings.setLanguage("zh_CN");break;
    default:
        break;
    }

    QMessageBox::information(this,"Settings","Apply Success!",QMessageBox::Ok);

}

void MainWindow::on_pushButton_reset_clicked()
{
     m_wsettings.setDefaultConfig();
     this->initUIValue();
     QMessageBox::information(this,"Settings","Reset Success!",QMessageBox::Ok);
}

void MainWindow::on_actionAbout_triggered()
{
    About *aboutDlg = new About;
    aboutDlg->show();
    aboutDlg->exec();
}

void MainWindow::updateClients(QStringList clients)
{
    for(int i=0;i<clients.size();i++)
        cout<<"clients:"<<clients.at(i).toStdString()<<endl;
}

