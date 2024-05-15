#include <PythonQt.h>
#include <QCoreApplication>

int main(int argc, char **argv)
{
    QCoreApplication qapp(argc, argv);
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    PythonQt::cleanup();
}

