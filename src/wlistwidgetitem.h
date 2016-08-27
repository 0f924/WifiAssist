#ifndef WLISTWIDGETITEM_H
#define WLISTWIDGETITEM_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class WListWidgetItem;
}

class WListWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WListWidgetItem(QWidget *parent = 0);
    explicit WListWidgetItem(QWidget *parent,const QString &hostname,const QString &mac);
    ~WListWidgetItem();

private:
    Ui::WListWidgetItem *ui;
};

#endif // WLISTWIDGETITEM_H
