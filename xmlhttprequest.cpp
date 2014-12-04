#include "xmlhttprequest.h"
#include <QJSValueList>
#include <assert.h>

XmlHttpRequest::XmlHttpRequest(QQmlEngine *qmlEngine, QObject *parent) :
    QObject(parent),
    qmlEngine(qmlEngine),
    withCredentials(false),
    timeout(0)
{
    qmlXhr = qmlEngine->globalObject().property("XMLHttpRequest");
   // assert(!qmlXhr.isNull() && !qmlXhr.isError());
}

void XmlHttpRequest::open(QJSValue method, QJSValue url, bool async, QJSValue username, QJSValue password)
{
     qmlXhr.property("open").call(QJSValueList() << method << url << async << username << password);
}

void XmlHttpRequest::setRequestHeader(QJSValue header, QJSValue value)
{
    qmlXhr.property("setRequestHeader").call(QJSValueList() << header << value);
}

void XmlHttpRequest::send(QJSValue data)
{
    qmlXhr.property("send").call(QJSValueList() << data);
}

void XmlHttpRequest::abort()
{
    qmlXhr.property("abort").call();
}

QJSValue XmlHttpRequest::getResponseHeader(QJSValue header)
{
    return     qmlXhr.property("getResponseHeader").call(QJSValueList() << header);
}

QJSValue XmlHttpRequest::getAllResponseHeaders()
{
        return     qmlXhr.property("getResponseHeaders").call();
}

void XmlHttpRequest::overrideMimeType(QJSValue mime)
{
        qmlXhr.property("overrideMimeType").call(QJSValueList() << mime);
}
