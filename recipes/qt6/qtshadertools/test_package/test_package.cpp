#include <QCoreApplication>
#include <QIODevice>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QFile file(":/wobble.frag.qsb");
    if(!file.open(QIODevice::ReadOnly)) {
        return 1;
    }

    return 0;
}
