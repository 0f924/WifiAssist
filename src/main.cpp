#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include "QWindow"
#include "singleapplication/singleapplication.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("{WifiAssist}");
    QApplication::setOrganizationName("{lzjqsdd}");

    //QApplication a(argc, argv);
    SingleApplication a(argc,argv);
    a.setWindowIcon(QIcon("img/WifiAssit.ico"));
    MainWindow w;
    w.show();
    return a.exec();
}
