#include "wlistwidgetitem.h"
#include "ui_wlistwidgetitem.h"
#include <QPicture>

WListWidgetItem::WListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WListWidgetItem)
{
    ui->setupUi(this);
}


WListWidgetItem::WListWidgetItem(QWidget *parent,const QString &hostname, const QString &mac) :
    QWidget(parent),
    ui(new Ui::WListWidgetItem)
{
    ui->setupUi(this);
    ui->label_hostname->setText(hostname);
    ui->label_mac->setText(mac);

    QPicture qp = QPicture();
    qp.load("/home/lzjqsdd/github/WifiAssist/INSTALL/img/edit.ico");
    ui->label_logo->setPicture(qp);
}


WListWidgetItem::~WListWidgetItem()
{
    delete ui;
}
