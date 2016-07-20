#ifndef WTHREAD_H
#define WTHREAD_H
#include <QThread>
#include "wsettings.h"

class WThread : public QThread
{
public:
    WThread();
    ~WThread();
private:
    WSettings *_settings;
signals:
    void updateUI(QStringList);
protected:
    void run();
};

#endif // WTHREAD_H
