#ifndef XMLHTTPREQUEST_H
#define XMLHTTPREQUEST_H

#include <QObject>
#include <QJSValue>
#include <QQmlEngine>

class XmlHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit XmlHttpRequest(QQmlEngine* qmlEngine, QObject *parent = 0);

signals:
  void onreadystatechange();

public slots:

public:
  // states
  const unsigned short UNSENT = 0;
  const unsigned short OPENED = 1;
  const unsigned short HEADERS_RECEIVED = 2;
  const unsigned short LOADING = 3;
  const unsigned short DONE = 4;
  int readyState;

  // request
 // void open(QJSValue *method, QJSValue *url);
  void open(QJSValue method, QJSValue url, bool async = true, QJSValue username = 0, QJSValue password=0);
  void setRequestHeader(QJSValue header, QJSValue value);
   int timeout;
  bool withCredentials;
  //readonly attribute XMLHttpRequestUpload upload;
  void send(QJSValue data);// = null);
  void abort();

  // response
  int status;
  QJSValue* statusText;
 QJSValue getResponseHeader(QJSValue header);
  QJSValue getAllResponseHeaders();
  void overrideMimeType(QJSValue mime);
  QJSValue* responseType;
  QJSValue* response;
  QJSValue* responseText;
  QJSValue* responseXML;

private:
  QQmlEngine* qmlEngine;
  QJSValue qmlXhr;

};

#endif // XMLHTTPREQUEST_H
