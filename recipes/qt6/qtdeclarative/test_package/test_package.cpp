#include <QDebug>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickStyle>
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Basic");
    if (QQuickStyle::name() != "Basic")
    {
        return 1;
    }

    QQmlEngine engine;
    QQmlComponent object(&engine);
    object.setData("import QtQml\nQtObject { property int answer: 6 * 7 }", QUrl());
    QScopedPointer<QObject> instance(object.create());
    if (!instance || instance->property("answer").toInt() != 42)
    {
        qDebug() << "QtQml component failed:" << object.errors();
        return 1;
    }

    QQmlComponent item(&engine);
    item.setData("import QtQuick\nRectangle { width: 30; height: 20; color: \"red\" }", QUrl());
    QScopedPointer<QQuickItem> rectangle(qobject_cast<QQuickItem *>(item.create()));
    if (!rectangle || rectangle->width() != 30 || rectangle->height() != 20)
    {
        qDebug() << "QtQuick component failed:" << item.errors();
        return 1;
    }
    return 0;
}
