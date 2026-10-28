#include <QCoreApplication>
#include <QDebug>
#include <QDomDocument>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QDomDocument document;
    const auto result = document.setContent(QByteArray(R"(<?xml version="1.0"?>
<library>
  <book id="1">Qt Xml</book>
  <book id="2">Qt Core</book>
</library>)"));
    if (!result)
    {
        qDebug() << "parse failed:" << result.errorMessage;
        return 1;
    }
    const QDomNodeList books = document.documentElement().elementsByTagName(QStringLiteral("book"));
    if (books.size() != 2 ||
        books.at(1).toElement().attribute(QStringLiteral("id")) != QStringLiteral("2") ||
        books.at(0).toElement().text() != QStringLiteral("Qt Xml"))
    {
        qDebug() << "unexpected document:" << document.toString();
        return 1;
    }
    return 0;
}
