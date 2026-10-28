#include <PythonQt.h>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication qapp(argc, argv);
    PythonQt::init(PythonQt::IgnoreSiteModule, "_PythonQt");

    PythonQtObjectPtr mainModule = PythonQt::self()->getMainModule();
    mainModule.evalScript(
        QStringLiteral("from PythonQt import QtCore, QtGui\n"
                       "host = QtCore.QUrl('https://example.org/index.html').host()\n"
                       "color = QtGui.QColor('red').name()\n"));
    const QString host = mainModule.getVariable("host").toString();
    const QString color = mainModule.getVariable("color").toString();
    int result = 0;
    if (PythonQt::self()->hadError() || host != QStringLiteral("example.org") ||
        color != QStringLiteral("#ff0000"))
    {
        qWarning() << "unexpected results from the Qt binding:" << host << color;
        result = 1;
    }

    PythonQt::cleanup();
    return result;
}
