#include <QApplication>
#include <QBuffer>
#include <QDebug>
#include <QHelpEngineCore>
#include <QLabel>
#include <QTemporaryDir>
#include <QUiLoader>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QApplication app(argc, argv);

    QByteArray ui =
        "<ui version=\"4.0\"><class>Form</class><widget class=\"QLabel\" name=\"label\">"
        "<property name=\"text\"><string>Hello</string></property></widget></ui>";
    QBuffer buffer(&ui);
    buffer.open(QIODevice::ReadOnly);
    QUiLoader loader;
    QWidget *widget = loader.load(&buffer);
    QLabel *label = qobject_cast<QLabel *>(widget);
    if (!label || label->text() != QStringLiteral("Hello"))
    {
        qWarning() << "loading the UI form failed:" << loader.errorString();
        return 1;
    }
    delete widget;

    QTemporaryDir tempDir;
    QHelpEngineCore helpEngine(tempDir.filePath(QStringLiteral("test_package.qhc")));
    if (!helpEngine.setupData())
    {
        qWarning() << "setting up the help engine failed:" << helpEngine.error();
        return 1;
    }
    if (!helpEngine.registeredDocumentations().isEmpty())
    {
        qWarning() << "unexpected registered documentations"
                   << helpEngine.registeredDocumentations();
        return 1;
    }
    return 0;
}
