#include "mainwindow.h"
#include <QApplication>
#include "singleinstance.h"
#include "QSimpleUpdater.h"

const QString UPDATES_URL = "https://raw.githubusercontent.com/lzjqsdd/WifiAssist/master/etc/UPDATES.json";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	//set application information
	app.setApplicationName("WifiAssist");
	app.setApplicationVersion("v0.6.2");
    app.setWindowIcon(QIcon("img/WifiAssit.ico"));

	//Prevent many instances of the app to be launcher
	QString name = "com.lzjqsdd.wifiassist";
	SingleInstance instance;
	if(instance.hasPrevious(name))
	{
		return EXIT_SUCCESS;
	}

	instance.listen(name);

	//Create and Show the app;
    MainWindow w;
    w.show();

    // Bring the WifiAssist window to the front
    QObject::connect(&instance, &SingleInstance::newInstance, [&](){
        (&w)->setMainWindowVisibility(true);
    });

    //Update WifiAssist
    QSimpleUpdater::getInstance()->setDownloaderEnabled(UPDATES_URL,true);
    QSimpleUpdater::getInstance()->setNotifyOnUpdate (UPDATES_URL, true);
    QSimpleUpdater::getInstance()->setNotifyOnFinish (UPDATES_URL, false);

    QSimpleUpdater::getInstance()->checkForUpdates (url);
    return app.exec();
}
