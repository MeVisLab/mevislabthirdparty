#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    if(!QSqlDatabase::drivers().contains("QSQLITE")) {
        qDebug() << "QSQLITE driver not found";
        return 1;
    }

    if(!QSqlDatabase::drivers().contains("QPSQL")) {
        qDebug() << "QPSQL driver not found";
        return 1;
    }

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qDebug() << "Failed to open QSQLITE database:" << db.lastError().text();
        return 1;
    }

    return 0;
}
