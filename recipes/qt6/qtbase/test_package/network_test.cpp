#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QNetworkInterface>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    const QHostAddress address(QStringLiteral("192.168.1.10"));
    if (address.protocol() != QAbstractSocket::IPv4Protocol ||
        !address.isInSubnet(QHostAddress(QStringLiteral("192.168.1.0")), 24) ||
        address.isInSubnet(QHostAddress(QStringLiteral("10.0.0.0")), 8))
    {
        qDebug() << "unexpected address:" << address;
        return 1;
    }
    if (QHostAddress(QHostAddress::LocalHostIPv6).toString() != QStringLiteral("::1"))
    {
        return 1;
    }

    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    qDebug() << "network interfaces:" << interfaces.size();
    for (const QNetworkInterface &interface : interfaces)
    {
        if (!interface.isValid())
        {
            return 1;
        }
    }
    return 0;
}
