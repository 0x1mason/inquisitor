#ifndef APPIUMENGINE_H
#define APPIUMENGINE_H
#include <QJSEngine>
 #include <QTimerEvent>
#include <qjsengine.h>
#include <QObject>
#include <QJsonObject>
#include "eventtimer.h"

class AppiumEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppiumEngine(QObject *parent = 0);
    void openDriver(QJsonObject &caps);
signals:
    void scriptError(const QJSValue &error);
public slots:

private:
static EventTimer *timer;
static QJSValue new_XmlHttpRequest();
    QJSEngine engine;

    void tryEmitScriptError();
    void startWebDriver();

    void addTimers();
    void loadModule(const QString &path, const QString &moduleName);
};

#endif // APPIUMENGINE_H
