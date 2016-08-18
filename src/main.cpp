#include "mainwindow.h"
#include "singleinstance.h"
#include "QSimpleUpdater.h"

#include <QApplication>

const QString UPDATES_URL = "https://raw.githubusercontent.com/lzjqsdd/WifiAssist/master/etc/UPDATES.json";

int main(int argc, char *argv[])
{
    QApplication::setDesktopSettingsAware(false);
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
    // Disable the integrated downloader, just open a link in a web browser
    QSimpleUpdater::getInstance()->setDownloaderEnabled (UPDATES_URL, false);

    // Only notify the user when an update is available
    QSimpleUpdater::getInstance()->setNotifyOnUpdate (UPDATES_URL, true);
    QSimpleUpdater::getInstance()->setNotifyOnFinish (UPDATES_URL, false);

    // Check for updates
    QSimpleUpdater::getInstance()->checkForUpdates (UPDATES_URL);
    return app.exec();
}
