#include <QCoreApplication>
#include <QByteArray>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QByteArray arr { "Hello Qt Core" };
    auto s = QString::fromLatin1(arr);
    qDebug() << s;

    return 0;
}
