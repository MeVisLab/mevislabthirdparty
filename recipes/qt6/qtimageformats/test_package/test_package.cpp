#include <QBuffer>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    const QList<QByteArray> formats = QImageReader::supportedImageFormats();
    for (const char *format : {"tiff", "webp"})
    {
        if (!formats.contains(format))
        {
            qDebug() << "image format not supported:" << format << formats;
            return 1;
        }
    }

    QImage image(4, 4, QImage::Format_RGB32);
    image.fill(Qt::red);
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    QImageWriter writer(&buffer, "tiff");
    if (!writer.write(image))
    {
        qDebug() << "writing tiff failed:" << writer.errorString();
        return 1;
    }
    buffer.seek(0);
    QImageReader reader(&buffer, "tiff");
    const QImage decoded = reader.read();
    if (decoded.size() != image.size() || decoded.pixel(1, 1) != image.pixel(1, 1))
    {
        qDebug() << "tiff round trip failed:" << reader.errorString();
        return 1;
    }
    return 0;
}
