#include "wlistwidgetitem.h"
#include "ui_wlistwidgetitem.h"
#include <QPicture>
#include <QBitmap>

WListWidgetItem::WListWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WListWidgetItem)
{
    ui->setupUi(this);
}


WListWidgetItem::WListWidgetItem(QWidget *parent,const QString &logoname,const QString &hostname, const QString &mac) :
    QWidget(parent),
    ui(new Ui::WListWidgetItem)
{
    ui->setupUi(this);
    ui->label_hostname->setText(hostname);
    ui->label_mac->setText(mac);
    QPixmap original = QPixmap(":cor/img/corpicon/"+logoname+".ico").scaled(50,50);
    ui->label_logo->setPixmap(PixmapToRound(original,15));
}


WListWidgetItem::~WListWidgetItem()
{
    delete ui;
}

QPixmap WListWidgetItem::PixmapToRound(const QPixmap &src, int radius)
{
        if (src.isNull()) {
            return QPixmap();
        }

        QSize size(2*radius, 2*radius);
        QBitmap mask(size);
        QPainter painter(&mask);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
        painter.setBrush(QColor(0, 0, 0));
        painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

        QPixmap image = src.scaled(size);
        image.setMask(mask);
        return image;
}
