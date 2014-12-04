#include "appiumengine.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QtDebug>
#include <QtQml>
#include <assert.h>
#include <xmlhttprequest.h>
QQmlEngine *engine2;
QJSEngine* engine3;
//QScriptEngine *AppiumEngine::_engine = new QScriptEngine();
EventTimer *AppiumEngine::timer = 0;
AppiumEngine::AppiumEngine(QObject *parent) :
    QObject(parent),
    engine()
{
    engine2 = new QQmlEngine();
    engine3 = &engine;
  //  auto xhr = engine2->globalObject().property("XMLHttpRequest");

   // assert(!xhr.isNull());
  //  engine2->evaluate("import \":/tools/webdriver.js\" as exports");
    //engine.globalObject().setProperty("XMLHttpRequest", xhr);
  //  QScriptEngineDebugger* debugger = new QScriptEngineDebugger();
 //   debugger->attachTo(&engine);
 //   debugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
    addTimers();

   //     QScriptContext* newContext = engine.pushContext();
  //  loadModule(":/tools/env.js", "Envjs");
    loadModule(":/tools/webdriver.js", "webdriver");
//assert(!engine2->globalObject().property("exports").isNull());
        startWebDriver();
}

void AppiumEngine::openDriver(QJsonObject &caps) {

}

QJSValue AppiumEngine::new_XmlHttpRequest()
{
    return engine3->newQObject(new XmlHttpRequest(engine2));
}

void AppiumEngine::tryEmitScriptError()
{
    //if (engine.hasUncaughtException())
    //    emit scriptError(engine.uncaughtException());
}


void AppiumEngine::addTimers()
{
    engine.globalObject().setProperty("setInterval", EventTimer::setInterval);
    engine.globalObject().setProperty("clearInterval", EventTimer::clearInterval);

    engine.globalObject().setProperty("setTimeout", EventTimer::setTimeout);
    engine.globalObject().setProperty("clearTimeout", EventTimer::clearTimeout);
    engine.globalObject().setProperty("new_XMLHttpRequest", AppiumEngine::new_XmlHttpRequest);
}

void AppiumEngine::loadModule(const QString &path, const QString &moduleName)
{
    QFile scriptFile(path);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        // handle error
    }
    QJSValue y = engine.evaluate(scriptFile.readAll(), path);
    qDebug() << y.toString();
    scriptFile.close();
}


void AppiumEngine::startWebDriver()
{
//engine.evaluate("Envjs();");
QJSValue y = engine.evaluate("var foo = new webdriver.Builder().usingServer('http://localhost:4723/wd/hub').withCapabilities({'browserName': 'qtwebkit', 'browserStartWindow': '*'});foo.build();");
qDebug() << y.toString();engine.dumpObjectInfo();
  //  auto v = engine2->globalObject().property("exports");
 //   assert(!v.property("foo").isNull() && !v.property("foo").isError());
 //   v.property("foo").call();
    QJSValue x = engine.evaluate("typeof webdriver === 'undefined';");
qDebug() << x.toString();
}
