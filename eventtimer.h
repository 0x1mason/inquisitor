#ifndef TIMER_H
#define TIMER_H
#include <QJSEngine>
 #include <QTimerEvent>

#include <QJSValue>
#include <QObject>
class EventTimer: public QObject
{
         Q_OBJECT
public:
    EventTimer(QJSEngine *engine);
 //       explicit EventTimer(QObject *parent = 0);
    static QJSValue setTimeout(QJSValue *, QJSValue *);
    static QJSValue clearTimeout(QJSValue *, QJSValue *);
    static QJSValue setInterval(QJSValue *, QJSValue *);
    static QJSValue clearInterval(QJSValue *, QJSValue *);

protected:
        void timerEvent(QTimerEvent *event);

private:
        QJSEngine *engine;
    static const QString TIMER_STATE_TOKEN;
    int doSetInterval(const QJSValue &expression, int delay);
    void doClearInterval(int timerId);

    int doSetTimeout(const QJSValue &expression, int delay);
    void doClearTimeout(int timerId);

    QHash<int, QJSValue> intervalHash;
    QHash<int, QJSValue> timeoutHash;
    static void tryEmitScriptError(QJSEngine *engine);
    void scriptException(const QJSValue &exception);

    static EventTimer *getTimerState(QJSEngine *engine);
signals:
    //void scriptError(const QScriptValue &error);
};

#endif // TIMER_H
