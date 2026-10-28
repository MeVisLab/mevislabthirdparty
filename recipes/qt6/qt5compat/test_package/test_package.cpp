#include <QCoreApplication>
#include <QDebug>
#include <QRegExp>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("ISO-8859-1");
    if (!codec)
    {
        qDebug() << "codec not available:" << QTextCodec::availableCodecs();
        return 1;
    }
    const QString text = QStringLiteral("café");
    const QByteArray encoded = codec->fromUnicode(text);
    if (encoded != QByteArray("caf\xe9") || codec->toUnicode(encoded) != text)
    {
        qDebug() << "codec round trip failed:" << encoded;
        return 1;
    }

    QRegExp expression(QStringLiteral("(\\d+)-(\\d+)"));
    if (expression.indexIn(QStringLiteral("range 10-20")) != 6 ||
        expression.cap(2) != QStringLiteral("20"))
    {
        qDebug() << "regular expression failed:" << expression.capturedTexts();
        return 1;
    }
    return 0;
}
