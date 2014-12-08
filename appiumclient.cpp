 #include <QObject>
#include "appiumclient.h"

AppiumClient::AppiumClient(const QUrl &url, QObject *parent) :
    QObject(parent),
      m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &AppiumClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &AppiumClient::closed);
        //m_webSocket.setSslConfiguration();
    m_webSocket.open(QUrl(url));

}

QString s(
        "var serverConfig = {\
          host: 'localhost',\
          port: 4723\
        };\
            driver = wd.remote(serverConfig);\
        \
            var desired = {\
               \"appium-version\": \"1.3\", \
                platformName: \"iOS\",\
                platformVersion: \"8.1\",\
                deviceName: \"iPhone Simulator\",\
                app: \"/Users/saucelabs/SauceLabs/appium/sample-code/apps/TestApp/build/Release-iphonesimulator/TestApp.app\"\
            };\
            driver.init(desired, function(v){if(v)_ws.send(v.toString());});"
        );

void AppiumClient::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &AppiumClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(s);
}

void AppiumClient::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
  //  m_webSocket.close();
}
