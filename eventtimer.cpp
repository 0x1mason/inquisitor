#include "eventtimer.h"
#include <assert.h>
#include <QTimerEvent>
#include <QtDebug>
const QString EventTimer::TIMER_STATE_TOKEN = "_$$timer_state$$_";

EventTimer::EventTimer(QJSEngine *engine): QObject(engine), engine(engine), intervalHash(), timeoutHash()
{

}

//EventTimer::EventTimer(QObject *parent) :
//    QObject(parent),
//    engine(0)
//{

//}

int EventTimer::doSetTimeout(const QJSValue &expression, int delay)
{
    if (expression.isString() || expression.isCallable()) {
        int timerId = startTimer(delay);
        timeoutHash.insert(timerId, expression);
        return timerId;
    }
    return -1;
}


void EventTimer::doClearTimeout(int timerId)
{
    killTimer(timerId);
    timeoutHash.remove(timerId);
}


int EventTimer::doSetInterval(const QJSValue &expression, int delay)
{

    if (expression.isString() || expression.isCallable()) {
        int timerId = startTimer(delay);
        intervalHash.insert(timerId, expression);
        return timerId;
    }
    return -1;
}


void EventTimer::doClearInterval(int timerId)
{
    killTimer(timerId);
    intervalHash.remove(timerId);
}


void EventTimer::timerEvent(QTimerEvent *event)
{
    int id = event->timerId();
    auto expression = intervalHash.value(id);

    if (expression.isNull()) {
        expression = timeoutHash.value(id);
        if (!expression.isNull())
            this->killTimer(id);
    }
    if (expression.isString()) {
        engine->evaluate(expression.toString());
    } else if (expression.isCallable()) {
        expression.call();
    }
    tryEmitScriptError(engine);
}



void EventTimer::scriptException(const QJSValue & exception) {
//    qDebug() << "ScriptException:" << this->engine->uncaughtExceptionLineNumber() << exception.toString();
//    qDebug() << "Backtrace:";
//    foreach( QString row, this->engine->uncaughtExceptionBacktrace() ) {
//    qDebug() << row;
//    }
//    this->engine->clearExceptions();
}


EventTimer* EventTimer::getTimerState(QJSEngine *engine)
{
    auto timeObj = engine->globalObject().property(TIMER_STATE_TOKEN);
    if (!timeObj.isObject())
    {
        timeObj = engine->toScriptValue(new EventTimer(engine));
        engine->globalObject().setProperty(TIMER_STATE_TOKEN, timeObj);
    }

    return qobject_cast<EventTimer*>(timeObj.toQObject());
}

QJSValue EventTimer::setTimeout(QJSValue *a, QJSValue *b)
{
auto timer = getTimerState(a->engine());
return timer ->doSetTimeout(*(a), b->toInt());
}


QJSValue EventTimer::clearTimeout(QJSValue *a, QJSValue *b)
{
    auto timer = getTimerState(a->engine());
   timer ->doClearTimeout(a->toInt());
}


QJSValue EventTimer::setInterval(QJSValue *a, QJSValue *b)
{
    auto timer = getTimerState(a->engine());
return timer ->doSetInterval(*(a), a->toInt());
}


QJSValue EventTimer::clearInterval(QJSValue *a, QJSValue *b)
{
    auto timer = getTimerState(a->engine());
timer ->doClearInterval(a->toInt());
}


void EventTimer::tryEmitScriptError(QJSEngine *engine)
{
   //if (engine->hasUncaughtException())
   //    qDebug() << engine->->uncaughtException().toString();
   //    emit scriptError(engine->uncaughtException());
}
