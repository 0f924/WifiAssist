#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->text_About->setEnabled(false);
    showAbout();
}

About::~About()
{
    delete ui;
}

void About::showAbout()
{
    QString text_about = tr("WifiAssist 基于QT5开发，帮助用户在Linux系统上快速建立热点的小工具"
                         "项目地址：www.github.com/lzjqsdd/WifiAssist");

    ui->text_About->setText(text_about);
}
