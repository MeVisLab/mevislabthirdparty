#include <SingleApplication>

int main(int argc, char **argv)
{
    SingleApplication app(argc, argv);

    if (app.sendMessage("Do I exist?")) {
        return 0;
    }

    return 0;
}
