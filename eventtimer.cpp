#include "eventtimer.h"
#include <assert.h>
#include <QTimerEvent>
#include <QtDebug>
const QString EventTimer::TIMER_STATE_TOKEN = "_$$timer_state$$_";

EventTimer::EventTimer(QScriptEngine *engine): QObject(engine), engine(engine), intervalHash(), timeoutHash()
{

}

//EventTimer::EventTimer(QObject *parent) :
//    QObject(parent),
//    engine(0)
//{

//}

int EventTimer::doSetTimeout(const QScriptValue &expression, int delay)
{
    if (expression.isString() || expression.isFunction()) {
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


int EventTimer::doSetInterval(const QScriptValue &expression, int delay)
{
    if (expression.isString() || expression.isFunction()) {
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
    QScriptValue expression = intervalHash.value(id);
    if (!expression.isValid()) {
        expression = timeoutHash.value(id);
        if (expression.isValid())
            this->killTimer(id);
    }
    if (expression.isString()) {
        engine->evaluate(expression.toString());
    } else if (expression.isFunction()) {
        expression.call();
    }
    tryEmitScriptError(engine);
}



void EventTimer::scriptException(const QScriptValue & exception) {
//    qDebug() << "ScriptException:" << this->engine->uncaughtExceptionLineNumber() << exception.toString();
//    qDebug() << "Backtrace:";
//    foreach( QString row, this->engine->uncaughtExceptionBacktrace() ) {
//    qDebug() << row;
//    }
//    this->engine->clearExceptions();
}


EventTimer* EventTimer::getTimerState(QScriptEngine *engine)
{
    auto timeObj = engine->globalObject().property(TIMER_STATE_TOKEN);
    if (!timeObj.isObject())
    {
        timeObj = engine->toScriptValue(new EventTimer(engine));
        engine->globalObject().setProperty(TIMER_STATE_TOKEN, timeObj);
    }

    return qobject_cast<EventTimer*>(timeObj.toQObject());
}

QScriptValue EventTimer::setTimeout(QScriptContext *context, QScriptEngine *engine)
{
auto timer = getTimerState(engine);
return timer ->doSetTimeout(context->argument(0), context->argument(1).toInteger());
}


QScriptValue EventTimer::clearTimeout(QScriptContext *context, QScriptEngine *engine)
{
    auto timer = getTimerState(engine);
   timer ->doClearTimeout(context->argument(0).toInteger());
}


QScriptValue EventTimer::setInterval(QScriptContext *context, QScriptEngine *engine)
{
    auto timer = getTimerState(engine);
return timer ->doSetInterval(context->argument(0), context->argument(1).toInteger());
}


QScriptValue EventTimer::clearInterval(QScriptContext *context, QScriptEngine *engine)
{
    auto timer = getTimerState(engine);
timer ->doClearInterval(context->argument(0).toInteger());
}


void EventTimer::tryEmitScriptError(QScriptEngine *engine)
{
   if (engine->hasUncaughtException())
       qDebug() << engine->uncaughtException().toString();
   //    emit scriptError(engine->uncaughtException());
}
