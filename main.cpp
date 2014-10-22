#include <QCoreApplication>
#include "HTTPServerQT.h"
#include "httpserver.h"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    HTTPServer srv(NULL);
    return app.exec();
}
