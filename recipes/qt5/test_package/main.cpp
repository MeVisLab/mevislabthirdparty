#include <QString>
#include <QWidget>
#include <QWebEngineView>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString s;
    auto w = new QWidget;
    new QWebEngineView(w);

    delete w;
}
