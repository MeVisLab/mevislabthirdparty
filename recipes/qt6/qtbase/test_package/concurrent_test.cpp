#include <QCoreApplication>
#include <QtConcurrent>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList strings { QStringLiteral("Hello"), QStringLiteral("Qt"), QStringLiteral("Concurrent") };
    auto lowerStrings = QtConcurrent::blockingMapped(strings, [](const auto &s) { return s.toLower(); });
    if(lowerStrings == QStringList{ QStringLiteral("hello"), QStringLiteral("qt"), QStringLiteral("concurrent") }) {
        return 0;
    }
    return 1;
}
