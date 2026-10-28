#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QWebSocket>
#include <QWebSocketServer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    int result = 1;

    QWebSocketServer server(QStringLiteral("test_package"), QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost))
    {
        qWarning() << "listen failed:" << server.errorString();
        return 1;
    }
    QObject::connect(
        &server, &QWebSocketServer::newConnection, &server,
        [&server]()
        {
            QWebSocket *socket = server.nextPendingConnection();
            QObject::connect(socket, &QWebSocket::textMessageReceived, socket,
                             [socket](const QString &message)
                             { socket->sendTextMessage(QStringLiteral("echo: ") + message); });
            QObject::connect(socket, &QWebSocket::disconnected, socket, &QObject::deleteLater);
        });

    QWebSocket client;
    QObject::connect(&client, &QWebSocket::connected, &client,
                     [&client]() { client.sendTextMessage(QStringLiteral("ping")); });
    QObject::connect(&client, &QWebSocket::textMessageReceived, &client,
                     [&](const QString &message)
                     {
                         result = message == QStringLiteral("echo: ping") ? 0 : 1;
                         app.quit();
                     });
    QObject::connect(&client, &QWebSocket::errorOccurred, &client,
                     [&](QAbstractSocket::SocketError)
                     {
                         qWarning() << "client error:" << client.errorString();
                         app.quit();
                     });
    QTimer::singleShot(10000, &app, &QCoreApplication::quit);

    client.open(server.serverUrl());
    app.exec();
    return result;
}
