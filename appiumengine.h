#ifndef APPIUMENGINE_H
#define APPIUMENGINE_H
#include <QtScript/QScriptEngine>
 #include <QTimerEvent>

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
    void scriptError(const QScriptValue &error);
public slots:

private:
static EventTimer *timer;

    QScriptEngine engine;

    void tryEmitScriptError();
    void startWebDriver();

    void addTimers();
    void loadModule(const QString &path, const QString &moduleName);
};

#endif // APPIUMENGINE_H
