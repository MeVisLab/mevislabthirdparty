#include <QApplication>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineView>
#include <QtWebEngineQuick>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    qputenv("QTWEBENGINE_DISABLE_SANDBOX", "1");
    QtWebEngineQuick::initialize();
    QApplication app(argc, argv);

    QWebEngineProfile profile;
    QWebEnginePage page(&profile);
    QWebEngineView view;
    view.setPage(&page);

    bool loaded = false;
    QEventLoop loop;
    QObject::connect(&page, &QWebEnginePage::loadFinished, &loop,
                     [&](bool success)
                     {
                         loaded = success;
                         loop.quit();
                     });
    QTimer::singleShot(60000, &loop, &QEventLoop::quit);
    page.setHtml(
        QStringLiteral("<html><head><title>test_package</title></head><body></body></html>"));
    loop.exec();

    if (!loaded || view.title() != QStringLiteral("test_package"))
    {
        qWarning() << "loading the page failed, title:" << view.title();
        return 1;
    }
    return 0;
}
