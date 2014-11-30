#include "appiumengine.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtScriptTools/QtScriptTools>
//QScriptEngine *AppiumEngine::_engine = new QScriptEngine();
EventTimer *AppiumEngine::timer = 0;
AppiumEngine::AppiumEngine(QObject *parent) :
    QObject(parent),
    engine()
{

    QScriptEngineDebugger* debugger = new QScriptEngineDebugger();
    debugger->attachTo(&engine);
 //   debugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
    addTimers();
        QScriptContext* newContext = engine.pushContext();
  //  loadModule(":/tools/env.js", "Envjs");
    loadModule(":/tools/webdriver.js", "exports");

        startWebDriver();
}

void AppiumEngine::openDriver(QJsonObject &caps) {

}

void AppiumEngine::tryEmitScriptError()
{
    if (engine.hasUncaughtException())
        emit scriptError(engine.uncaughtException());
}


void AppiumEngine::addTimers()
{
    QScriptValue si = engine.newFunction(EventTimer::setInterval);
    engine.globalObject().setProperty("setInterval", si);
    QScriptValue ci = engine.newFunction(EventTimer::clearInterval);
    engine.globalObject().setProperty("clearInterval", ci);

    QScriptValue st = engine.newFunction(EventTimer::setTimeout);
    engine.globalObject().setProperty("setTimeout", st);
    QScriptValue ct = engine.newFunction(EventTimer::clearTimeout);
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
 //   engine.globalObject().setProperty(moduleName, moduleObject);;
  //  moduleObject = newContext->activationObject().property(moduleName);
  //  engine.popContext();
    scriptFile.close();
}


void AppiumEngine::startWebDriver()
{
//engine.evaluate("Envjs();");
QScriptValue x = engine.evaluate("foo = new webdriver.Builder().usingServer('http://localhost:4723/wd/hub').withCapabilities({'browserName': 'qtwebkit', 'browserStartWindow': '*'}).build();foo.get('http://www.google.com');");

QString d = x.toString();
}
