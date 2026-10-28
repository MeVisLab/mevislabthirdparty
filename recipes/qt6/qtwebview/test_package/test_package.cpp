#include <QDebug>
#include <QGuiApplication>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QScopedPointer>
#include <QtWebView>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QtWebView::initialize();
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData("import QtWebView\nimport QtQml\nQtObject { objectName: \"webview_import\" }",
                      QUrl());
    if (component.status() != QQmlComponent::Ready)
    {
        qWarning() << "importing QtWebView failed:" << component.errorString();
        return 1;
    }
    QScopedPointer<QObject> object(component.create());
    if (!object || object->objectName() != QStringLiteral("webview_import"))
    {
        qWarning() << "creating the component failed:" << component.errorString();
        return 1;
    }
    return 0;
}
