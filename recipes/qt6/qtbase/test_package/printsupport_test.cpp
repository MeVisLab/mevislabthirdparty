#include <QDebug>
#include <QFileInfo>
#include <QGuiApplication>
#include <QPainter>
#include <QPrinter>
#include <QPrinterInfo>
#include <QTemporaryDir>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QGuiApplication app(argc, argv);
    qDebug() << "printers:" << QPrinterInfo::availablePrinterNames();

    QTemporaryDir directory;
    if (!directory.isValid())
    {
        return 1;
    }
    const QString fileName = directory.filePath(QStringLiteral("test.pdf"));
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QPainter painter;
    if (!painter.begin(&printer))
    {
        qDebug() << "cannot paint on printer";
        return 1;
    }
    painter.drawText(100, 100, QStringLiteral("Hello PrintSupport"));
    painter.drawRect(100, 200, 500, 300);
    if (!painter.end() || QFileInfo(fileName).size() <= 0)
    {
        qDebug() << "pdf was not written:" << fileName;
        return 1;
    }
    return 0;
}
