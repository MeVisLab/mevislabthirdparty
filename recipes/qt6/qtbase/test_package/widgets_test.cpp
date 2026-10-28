#include <QApplication>
#include <QLabel>
#include <QPixmap>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QApplication app(argc, argv);

    QLabel label(QStringLiteral("Hello Widgets"));
    label.show();
    if (!label.isVisible() || label.text() != QStringLiteral("Hello Widgets") ||
        !label.sizeHint().isValid() || !QApplication::allWidgets().contains(&label))
    {
        return 1;
    }
    const QPixmap pixmap = label.grab();
    if (pixmap.isNull())
    {
        return 1;
    }
    return 0;
}
