#include <QtService>
#include <QCoreApplication>


class TestService : public QtService<QCoreApplication>
{
public:
	explicit TestService(int &argc, char **argv)
      : QtService<QCoreApplication>(argc, argv, "Test Daemon")
    {}

    void start() override {}
    void stop() override {}
};

int main(int argc, char **argv)
{
    TestService app(argc, argv);
    return 0;
}
