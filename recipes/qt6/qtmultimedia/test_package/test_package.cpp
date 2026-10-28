#include <QAudioDevice>
#include <QCoreApplication>
#include <QDebug>
#include <QMediaDevices>
#include <QMediaFormat>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    const QList<QAudioDevice> outputs = QMediaDevices::audioOutputs();
    qDebug() << "audio outputs:" << outputs.size();
    for (const QAudioDevice &device : outputs)
    {
        if (device.id().isEmpty())
        {
            qDebug() << "audio output without id:" << device.description();
            return 1;
        }
    }

    QMediaFormat format;
    if (format.fileFormat() != QMediaFormat::UnspecifiedFormat)
    {
        return 1;
    }
    format.setFileFormat(QMediaFormat::Wave);
    format.setAudioCodec(QMediaFormat::AudioCodec::Wave);
    if (format.fileFormat() != QMediaFormat::Wave ||
        QMediaFormat::fileFormatName(format.fileFormat()) != "Wave")
    {
        qDebug() << "unexpected file format:" << QMediaFormat::fileFormatName(format.fileFormat());
        return 1;
    }
    qDebug() << "decodable formats:" << format.supportedFileFormats(QMediaFormat::Decode).size();
    return 0;
}
