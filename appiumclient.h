#ifndef APPIUMCLIENT_H
#define APPIUMCLIENT_H
#include <QtWebSockets/QWebSocket>
#include <QObject>

class AppiumClient : public QObject
{
    Q_OBJECT
public:
    explicit AppiumClient(const QUrl &url, QObject *parent = 0);

signals:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // APPIUMCLIENT_H
