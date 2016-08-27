#include "wlistwidgetitem.h"
#include "ui_wlistwidgetitem.h"
#include <QPicture>
#include <QBitmap>
#include <QPainter>

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

    //ui->label_logo->setPixmap(QPixmap(":cor/img/corpicon/XiaomiCo.ico").scaled(40,40));

    QPixmap original = QPixmap(QString("/home/lzjqsdd/github/WifiAssist/resources/img/corpicon/Apple.ico"),"ico").scaled(40,40);
    // Draw the mask.
    QBitmap  mask(original.size());
    QPainter painter(&mask);
    mask.fill(Qt::white);
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(mask.width()/2, mask.height()/2), 30, 30);

    // Draw the final image.
    original.setMask(mask);
    ui->label_logo->setPixmap(original);
}


WListWidgetItem::~WListWidgetItem()
{
    delete ui;
}
