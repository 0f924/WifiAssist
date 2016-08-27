#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>
#include <src/wsettings.h>
#include <QCoreApplication>
#include <QVector>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mutex(0),
    m_information_count(0),
    m_wifi(new Wifi()),
    m_wsettings(new WSettings()),
    m_wdevices(new WDevices()),
    m_wthread(new WThread()),
    m_translator(new QTranslator(this)),
    m_trayIcon(new QSystemTrayIcon(this)),
    m_restoreAction(new QAction(this)),
    m_quitAction(new QAction(this)),
    m_controlWifi(new QAction(this)),
    m_restartWifi(new QAction(this)),
    m_trayIconMenu(new QMenu(this))
{
    setupLanguage();
    ui->setupUi(this);

    initUIValue();
    setupTrayIcon();
    setupSignalsSlots();

    setupDevicesForTest();
}

MainWindow::~MainWindow()
{
    m_wifi->stopWifi();
    delete ui;
}

void MainWindow::setupSignalsSlots()
{
    //signal-slot:
    //connect(_thread,SIGNAL(updateUI(QStringList)),this,SLOT(updateClients(QStringList)),Qt::QueuedConnection);

    qRegisterMetaType<QVector<Device*> >("QVector<Device*>");

    connect(m_restoreAction, &QAction::triggered, this, [this](){
        setMainWindowVisibility(isHidden()
                                || windowState() == Qt::WindowMinimized
                                || (qApp->applicationState() == Qt::ApplicationInactive));
    });
    connect(m_quitAction, &QAction::triggered, this, &MainWindow::close);
    connect(m_controlWifi,&QAction::triggered,this,&MainWindow::on_pushButton_clicked);
    connect(m_restartWifi,&QAction::triggered,this,[this](){
        ui->pushButton->setText("Restaring...");
        m_wifi->restartWifi();
        ui->pushButton->setText("STOP");
    });

    connect(m_wthread,SIGNAL(clientAdd(QVector<Device *>)),this,SLOT(updateNewClients(QVector<Device*>)),Qt::QueuedConnection);
    connect(m_wthread,SIGNAL(clientLeave(QVector<Device *>)),this,SLOT(updateLeaveClients(QVector<Device*>)),Qt::QueuedConnection);
    connect(m_wthread,SIGNAL(clientUpdate(QVector<Device*>)),this,SLOT(updateDevicesList(QVector<Device*>)),Qt::QueuedConnection);
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
        m_restoreAction->setText(tr("Hide WifiAssist"));
    }else{
        m_restoreAction->setText(tr("Show WifiAssist"));
        hide();
    }
}


void MainWindow::initUIValue()
{
    ui->tabWidget->setCurrentIndex(0);
    //ui->tabWidget->removeTab(1);

    ui->pushButton->setText("START");

    ui->lineEdit_name->setText(m_wsettings->APName());
    ui->lineEdit_pwd ->setText(m_wsettings->Password());
    ui->lineEdit_ap->setText(m_wsettings->AccessPoint());


    //get interface list
    QStringList interface_list = m_wsettings->getInterfaceList();

    ui->comboBox_createdinterface->clear();
    ui->comboBox_createdinterface->addItems(interface_list);
    ui->comboBox_createdinterface->setCurrentText(m_wsettings->Interface_Create());
    ui->comboBox_shareinterface->clear();
    ui->comboBox_shareinterface->addItems(interface_list);
    ui->comboBox_shareinterface->setCurrentText(m_wsettings->Interface_Shared());

    setupLanguageOption();
    ui->label_tip->setHidden(true);

    //init ui text
    ui->label_ap->setText(tr("AccessPoint"));
    ui->label_name->setText(tr("WifiName"));
    ui->label_pwd->setText(tr("Password"));
    ui->label_shareinterface->setText(tr("SharedInterface"));
    ui->label_createdinterface->setText(tr("APInterface"));
    ui->label_language->setText(tr("Language"));
    ui->comboBox_language->setCurrentIndex(0);
}

void MainWindow::setupLanguage()
{
    QString languageFile = QString(":/i18n/").append(m_wsettings->Language()).append(".qm");
    m_translator->load(languageFile);
    qApp->installTranslator(m_translator);
}

void MainWindow::setupTrayIcon()
{
    //Check if System Support SystemTrayIcon.
    //Linux:X11
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {

        m_restoreAction->setText(tr("&Hide WifiAssist"));
        m_quitAction->setText(tr("&Quit"));
        m_controlWifi->setText(tr("&Start Wifi"));
        m_restartWifi->setText(tr("Restart Wifi"));

        m_trayIconMenu->addAction(m_restoreAction);
        m_trayIconMenu->addSeparator();
        m_trayIconMenu->addAction(m_controlWifi);
        m_trayIconMenu->addAction(m_restartWifi);
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
        if(m_wifi->startWifi())
        {
            ui->pushButton->setText("STOP");
            m_controlWifi->setText(tr("Stop Wifi"));
            m_wthread->start();
        }
    }
    else if(QString::compare(text,"STOP") == 0)
    {
        if(m_wifi->stopWifi())
        {
            ui->pushButton->setText("START");
            m_controlWifi->setText(tr("Start Wifi"));
            m_wthread->stop();
        }
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
        if(ui->lineEdit_name->text() == m_wsettings->APName())
            return;

        ui->lineEdit_name->setEnabled(false);
        m_wsettings->setAPName(ui->lineEdit_name->text());

        //add apply tips
        ui->label_tip->setHidden(false);
        ui->label_tip->setText(tr("Apply WifiName Success!"));

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<3000)
            QCoreApplication::processEvents();
        ui->label_tip->setHidden(true);


        if(QString::compare(ui->pushButton->text(),"STOP") == 0)
        {
            ui->pushButton->setText("Restaring...");
            m_wifi->restartWifi();
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
        if(ui->lineEdit_pwd->text() == m_wsettings->Password())
            return;
        if(ui->lineEdit_pwd->text().size() < 8)
            QMessageBox::information(this,tr("Settings"),tr("Password Should More Than 8 Characters!"),QMessageBox::Warning);

        ui->lineEdit_pwd->setEnabled(false);
        m_wsettings->setPassword(ui->lineEdit_pwd->text());

        //add apply tips
        ui->label_tip->setHidden(false);
        ui->label_tip->setText(tr("Apply Password Success!"));

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<3000)
            QCoreApplication::processEvents();
        ui->label_tip->setHidden(true);

        if(QString::compare(ui->pushButton->text(),"STOP") == 0)
        {
            ui->pushButton->setText("Restaring...");
            m_wifi->restartWifi();
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
        QMessageBox::information(this,tr("Settings"),tr("Access Point Can't Be Empty!"),QMessageBox::Ok);
        return;
    }
    if(interface_created.size() == 0)
    {
        QMessageBox::information(this,tr("Settings"),tr("Wifi Interface Can't Be Empty!"),QMessageBox::Ok);
        return;
    }
    if(interface_shared.size() == 0)
    {
        QMessageBox::information(this,tr("Settings"),tr("Shared Interface Can't Be Empty!"),QMessageBox::Ok);
        return;
    }

    if(!interface_created.startsWith("wl"))
    {
        QMessageBox::StandardButton stdbtn = QMessageBox::warning(NULL,tr("Settings"),
                                                                  tr("This Wifi Interface May not work,Still Use it?"),
                                                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(stdbtn == QMessageBox::No)
            return;
    }
    if(!(interface_shared.contains("eth") || interface_shared.contains("en")) || interface_shared.contains("wl"))
    {
        QMessageBox::StandardButton stdbtn = QMessageBox::warning(NULL,tr("Settings"),
                                                                  tr("This Shared Interface May not work,Still Use it?"),
                                                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(stdbtn == QMessageBox::No)
            return;
    }

    m_wsettings->setAccessPoint(apoint);
    m_wsettings->setInterface_Create(interface_created);
    m_wsettings->setInterface_Shared(interface_shared);
    m_wsettings->setLanguage(m_languageList[ui->comboBox_language->currentIndex()]);

    QMessageBox::information(this,tr("Settings"),tr("Apply Success!"),QMessageBox::Ok);

}

void MainWindow::on_pushButton_reset_clicked()
{
    m_wsettings->setDefaultConfig();
    this->initUIValue();
    QMessageBox::information(this,tr("Settings"),tr("Reset Success!"),QMessageBox::Ok);
}

void MainWindow::on_actionAbout_triggered()
{
    About *aboutDlg = new About;
    aboutDlg->show();
    aboutDlg->exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_trayIcon->isVisible() && this->isVisible())
    {
        setMainWindowVisibility(false);
        if(m_information_count == 0)
        {
            m_trayIcon->showMessage(tr("WifiAssist"),tr("Minmize to SystemTray"),QSystemTrayIcon::Information,1000);
            m_information_count = 1;
        }
        event->ignore();
    }
    else
    {
        event->accept();
    }
}


QStringList MainWindow::findQmFiles()
{
    QDir dir(":/i18n/");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files,
                                          QDir::Name);
    QMutableStringListIterator i(fileNames);
    m_languageList.clear();
    while (i.hasNext()) {
        i.next();
        i.setValue(dir.filePath(i.value()));
        QString s = i.value();
        s.remove(0,7);
        s.remove(s.length()-3,3);
        m_languageList.push_back(s);
    }
    return fileNames;
}

QString MainWindow::languageName(const QString &qmFile)
{
    QTranslator translator;
    translator.load(qmFile);
    QString lan = translator.translate("MainWindow","English");
    return lan;
}

void MainWindow::setupLanguageOption()
{
    QStringList languageFileList = findQmFiles();
    for(int i=0;i<languageFileList.size();i++)
    {
        ui->comboBox_language->addItem(languageName(languageFileList[i]));
    }
}

void MainWindow::updateNewClients(QVector<Device *> device)
{
    QString hostname;
    for(int i=0;i<device.size();i++)
        hostname= hostname+device[i]->hostname()+"\n";

    m_trayIcon->showMessage(tr("WifiAssist"),hostname+tr("Connected To Your AP"),QSystemTrayIcon::Information,1000);
}

void MainWindow::updateLeaveClients(QVector<Device *> device)
{
    QString hostname;
    for(int i=0;i<device.size();i++)
        hostname= hostname+device[i]->hostname()+"\n";

    m_trayIcon->showMessage(tr("WifiAssist"),hostname+tr("Left Your AP"),QSystemTrayIcon::Information,1000);
}

void MainWindow::setupDevicesForTest()
{
   // Form *form = new Form(this,"test1","test1");
   // QListWidgetItem *listItem1 = new QListWidgetItem();
   // listItem1->setSizeHint(QSize(0, 50));

   // ui->listWidget->addItem(listItem1);
   // ui->listWidget->setItemWidget(listItem1,form);

    for(int i=0;i<10;i++)
    {
        WListWidgetItem *wListWidgetItem = new WListWidgetItem(this,QString("xiaomi"),QString("11:21:33:33:34:44"));
        QListWidgetItem *listItem  = new QListWidgetItem();
        listItem->setSizeHint(QSize(0,51));
        listItem->setBackgroundColor(QColor(0,0,0));
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem,wListWidgetItem);
    }




    WListWidgetItem *wListWidgetItem2 = new WListWidgetItem(this,QString("xiaomi2"),QString("11:21:66:33:34:44"));
    QListWidgetItem *listItem2  = new QListWidgetItem();
    listItem2->setSizeHint(QSize(0,51));
    ui->listWidget->addItem(listItem2);
    ui->listWidget->setItemWidget(listItem2,wListWidgetItem2);
}

void MainWindow::updateDevicesList(QVector<Device *> device)
{
    ui->listWidget->clear();
    for(int i=0;i<device.size();i++)
    {
        WListWidgetItem *wListWidgetItem = new WListWidgetItem(this,device[i]->hostname(),device[i]->mac());
        QListWidgetItem *listItem  = new QListWidgetItem();
        listItem->setSizeHint(QSize(0,51));
        ui->listWidget->addItem(listItem);
        ui->listWidget->setItemWidget(listItem,wListWidgetItem);
    }
}
