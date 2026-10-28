#include <QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QWebChannel>
#include <QWebChannelAbstractTransport>

class RecordingTransport : public QWebChannelAbstractTransport
{
  public:
    QJsonObject lastMessage;

    void sendMessage(const QJsonObject &message) override
    {
        lastMessage = message;
    }
};

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ value CONSTANT)
  public:
    int value() const
    {
        return 42;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Counter counter;
    QWebChannel channel;
    channel.registerObject(QStringLiteral("counter"), &counter);
    RecordingTransport transport;
    channel.connectTo(&transport);

    emit transport.messageReceived(QJsonObject{{"type", 3}, {"id", 1}}, &transport);

    const QJsonObject response = transport.lastMessage;
    const QJsonObject counterInfo = response.value("data").toObject().value("counter").toObject();
    bool foundValue = false;
    for (const QJsonValue &property : counterInfo.value("properties").toArray())
    {
        const QJsonArray entry = property.toArray();
        foundValue = foundValue || (entry.at(1).toString() == QStringLiteral("value") &&
                                    entry.at(3).toInt() == 42);
    }
    if (response.value("type").toInt() != 10 || response.value("id").toInt() != 1 || !foundValue)
    {
        qWarning() << "unexpected init response" << response;
        return 1;
    }
    return 0;
}

#include "test_package.moc"
