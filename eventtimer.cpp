#include "eventtimer.h"
#include <QTimerEvent>
EventTimer::EventTimer( QScriptEngine *engine): engine(engine)
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
        this->engine->evaluate(expression.toString());
    } else if (expression.isFunction()) {
        expression.call();
    }
    tryEmitScriptError();
}

void EventTimer::tryEmitScriptError()
{
    if (engine->hasUncaughtException())
        emit scriptError(engine->uncaughtException());
}

void EventTimer::scriptException(const QScriptValue & exception) {
//    qDebug() << "ScriptException:" << this->engine->uncaughtExceptionLineNumber() << exception.toString();
//    qDebug() << "Backtrace:";
//    foreach( QString row, this->engine->uncaughtExceptionBacktrace() ) {
//    qDebug() << row;
//    }
//    this->engine->clearExceptions();
}

