#ifndef XMLHTTPREQUEST_H
#define XMLHTTPREQUEST_H

#include <QObject>

class XMLHttpRequest : public QObject
{
    Q_OBJECT
public:
    explicit XMLHttpRequest(QObject *parent = 0);

signals:

public slots:

};

#endif // XMLHTTPREQUEST_H
