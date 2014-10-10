#include <QCoreApplication>
#include "HTTPServerQT.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    HTTPServerQT httpserverqt;
    return app.exec();
}
