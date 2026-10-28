#include <Inventor/Qt/SoQt.h>
#include <QCoreApplication>

#include <cstdio>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    SoQt::init("test_package");

    if (!SoQt::eventHandler() || SoQt::loopDetected())
    {
        fprintf(stderr, "SoQt event handler was not set up\n");
        return 1;
    }
    app.processEvents();
    return 0;
}
