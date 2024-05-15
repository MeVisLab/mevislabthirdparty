#include <QCoreApplication>
#include <QImage>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QImage img(1024, 1024, QImage::Format_Grayscale16);

    return 0;
}
