#ifndef TIMER_H
#define TIMER_H
#include <QtScript/QScriptEngine>
 #include <QTimerEvent>
#include <QScriptValue>
#include <QScriptEngine>
#include <QObject>
class EventTimer: public QObject
{
         Q_OBJECT
public:
    EventTimer( QScriptEngine *engine);
 //       explicit EventTimer(QObject *parent = 0);


    int doSetInterval(const QScriptValue &expression, int delay);
    void doClearInterval(int timerId);

    int doSetTimeout(const QScriptValue &expression, int delay);
    void doClearTimeout(int timerId);

private:
    QScriptEngine *engine;
    void timerEvent(QTimerEvent *event);
    QHash<int, QScriptValue> intervalHash;
    QHash<int, QScriptValue> timeoutHash;
    void tryEmitScriptError();
    void scriptException(const QScriptValue &exception);
signals:
    void scriptError(const QScriptValue &error);
};

#endif // TIMER_H
