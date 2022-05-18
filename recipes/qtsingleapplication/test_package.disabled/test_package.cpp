#include <QtSolutions/QtSingleCoreApplication>

int main(int argc, char **argv)
{
    QtSingleCoreApplication app("test_package", argc, argv);

    if (app.sendMessage("Do I exist?")) {
        return 0;
    }

    return 0;
}
