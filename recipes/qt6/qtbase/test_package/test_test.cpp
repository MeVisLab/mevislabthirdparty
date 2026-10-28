#include <QtTest>

class TestPackage : public QObject
{
    Q_OBJECT

  private slots:
    void stringHandling()
    {
        QCOMPARE(QStringLiteral("Qt Test").toLower(), QStringLiteral("qt test"));
        QVERIFY(QStringLiteral("Qt Test").startsWith(QStringLiteral("Qt")));
    }

    void signalSpy()
    {
        QObject object;
        QSignalSpy spy(&object, &QObject::objectNameChanged);
        object.setObjectName(QStringLiteral("renamed"));
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.takeFirst().at(0).toString(), QStringLiteral("renamed"));
    }
};

QTEST_GUILESS_MAIN(TestPackage)
#include "test_test.moc"
