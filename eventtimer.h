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
    EventTimer(QScriptEngine *engine);
 //       explicit EventTimer(QObject *parent = 0);
    static QScriptValue setTimeout(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue clearTimeout(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue setInterval(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue clearInterval(QScriptContext *context, QScriptEngine *engine);

protected:
        void timerEvent(QTimerEvent *event);

private:
        QScriptEngine *engine;
    static const QString TIMER_STATE_TOKEN;
    int doSetInterval(const QScriptValue &expression, int delay);
    void doClearInterval(int timerId);

    int doSetTimeout(const QScriptValue &expression, int delay);
    void doClearTimeout(int timerId);

    QHash<int, QScriptValue> intervalHash;
    QHash<int, QScriptValue> timeoutHash;
    static void tryEmitScriptError(QScriptEngine *engine);
    void scriptException(const QScriptValue &exception);

    static EventTimer *getTimerState(QScriptEngine *engine);
signals:
    //void scriptError(const QScriptValue &error);
};

#endif // TIMER_H
