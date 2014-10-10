#ifndef HTTPServerQTTEST_H
#define HTTPServerQTTEST_H

#include <QtCore/QObject>
#include <QtTest/QTest>

class HTTPServerQTTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();
    void someTest();
};

#endif // HTTPServerQTTEST_H
