#ifndef WLISTWIDGETITEM_H
#define WLISTWIDGETITEM_H

#include <QWidget>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

namespace Ui {
class WListWidgetItem;
}

class WListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WListWidgetItem(QWidget *parent = 0);
    explicit WListWidgetItem(QWidget *parent,const QString &logoname,const QString &hostname,const QString &mac);
    ~WListWidgetItem();

private:
    Ui::WListWidgetItem *ui;
    QPixmap PixmapToRound(const QPixmap &src, int radius);
};

#endif // WLISTWIDGETITEM_H
