#include <QApplication>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QSvgRenderer>
#include <QSvgWidget>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QApplication app(argc, argv);

    const QByteArray svg = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"16\" height=\"16\">"
                           "<rect width=\"16\" height=\"16\" fill=\"#ff0000\"/></svg>";
    QSvgRenderer renderer(svg);
    if (!renderer.isValid())
    {
        qWarning() << "failed to parse SVG";
        return 1;
    }
    QImage image(16, 16, QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    renderer.render(&painter);
    painter.end();
    if (image.pixelColor(8, 8) != QColor(Qt::red))
    {
        qWarning() << "unexpected pixel color" << image.pixelColor(8, 8);
        return 1;
    }

    QSvgWidget widget;
    widget.load(svg);
    if (!widget.renderer()->isValid() || widget.sizeHint() != QSize(16, 16))
    {
        qWarning() << "unexpected SVG widget size hint" << widget.sizeHint();
        return 1;
    }
    return 0;
}
