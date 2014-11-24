#include "appiumengine.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
//QScriptEngine *AppiumEngine::_engine = new QScriptEngine();
EventTimer *AppiumEngine::timer = 0;
AppiumEngine::AppiumEngine(QObject *parent) :
    QObject(parent),
    engine()
{
    if (!AppiumEngine::timer) {
        timer = new EventTimer(&engine);
    }
 //   addTimers();
        QScriptContext* newContext = engine.pushContext();
    loadModule("../../env.js", "Envjs");
    loadModule("../../webdriver.js", "exports");

        startWebDriver();
}

void AppiumEngine::openDriver(QJsonObject &caps) {

}

 QScriptValue AppiumEngine::setTimeout(QScriptContext *context, QScriptEngine *engine)
 {

timer ->doSetTimeout(context->argument(0), context->argument(1).toInteger());
 }


QScriptValue AppiumEngine::clearTimeout(QScriptContext *context, QScriptEngine *engine)
{
    timer ->doClearTimeout(context->argument(0).toInteger());
}


QScriptValue AppiumEngine::setInterval(QScriptContext *context, QScriptEngine *engine)
{
timer ->doSetInterval(context->argument(0), context->argument(1).toInteger());
}


QScriptValue AppiumEngine::clearInterval(QScriptContext *context, QScriptEngine *engine)
{
timer ->doClearInterval(context->argument(0).toInteger());
}


void AppiumEngine::tryEmitScriptError()
{
    if (engine.hasUncaughtException())
        emit scriptError(engine.uncaughtException());
}


void AppiumEngine::addTimers()
{
    QScriptValue si = engine.newFunction(setInterval);
    engine.globalObject().setProperty("setInterval", si);
    QScriptValue ci = engine.newFunction(clearInterval);
    engine.globalObject().setProperty("clearInterval", ci);

    QScriptValue st = engine.newFunction(setTimeout);
    engine.globalObject().setProperty("setTimeout", st);
    QScriptValue ct = engine.newFunction(clearTimeout);
    engine.globalObject().setProperty("clearTimeout", ct);
}

void AppiumEngine::loadModule(const QString &path, const QString &moduleName)
{
    QFile scriptFile(path);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        // handle error
    }


   // QScriptValue moduleObject = engine.newObject();
   // newContext->activationObject().setProperty(moduleName, moduleObject);
     engine.evaluate(scriptFile.readAll());
    //engine.globalObject().setProperty(moduleName, moduleObject);;
  //  moduleObject = newContext->activationObject().property(moduleName);
  //  engine.popContext();
    scriptFile.close();
}


void AppiumEngine::startWebDriver()
{
//engine.evaluate("Envjs();");
QScriptValue x = engine.evaluate("new webdriver.ExistingSessionBuilder().usingServer('http://localhost:4723/wd/hub').withCapabilities({'browserName': 'qtwebkit', 'browserStartWindow': '*'}).build();");

QString d = x.toString();
}
