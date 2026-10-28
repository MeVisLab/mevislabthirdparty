#include <PythonQt.h>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }
    QCoreApplication qapp(argc, argv);
    PythonQt::init(PythonQt::IgnoreSiteModule, "_PythonQt");
    PythonQt::self()->getMainModule().evalFile(argv[1]);
    const bool failed = PythonQt::self()->hadError();
    PythonQt::cleanup();
    return failed ? 1 : 0;
}
