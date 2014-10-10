#include "HTTPServerQTTest.h"

void HTTPServerQTTest::initTestCase()
{}

void HTTPServerQTTest::init()
{}

void HTTPServerQTTest::cleanup()
{}

void HTTPServerQTTest::cleanupTestCase()
{}

void HTTPServerQTTest::someTest()
{
    QCOMPARE(1,2);
}

QTEST_MAIN(HTTPServerQTTest)

#include "HTTPServerQTTest.moc"
