#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

class HttpServer : public QObject
{
    Q_OBJECT

public:
	explicit HttpServer(QObject *parent = nullptr)
      : m_server(new QHttpServer(this))
    {
        connect(m_server, &QHttpServer::newRequest, this, &HttpServer::handleRequest);
        m_server->listen(QHostAddress::LocalHost, 9572);
    }

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp)
    {
        Q_UNUSED(req)
        resp->setHeader("Content-Type", "text/plain");
        resp->writeHead(200);
        resp->end("Hello, world!");
    }

private:
    QHttpServer *m_server = nullptr;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    HttpServer server;

    QNetworkAccessManager manager;
    manager.setTransferTimeout(2000);
    QObject::connect(&manager, &QNetworkAccessManager::finished, [](auto *reply) {
        qDebug() << reply->readAll();
        reply->deleteLater();
        QCoreApplication::exit(reply->error() == QNetworkReply::NoError ? 0 : 1);
    });

    manager.get(QNetworkRequest(QUrl("http://localhost:9572")));

    app.exec();
}

#include "test_package.moc"
