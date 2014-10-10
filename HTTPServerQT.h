#ifndef HTTPServerQT_H
#define HTTPServerQT_H

#include <QtCore/QObject>

class HTTPServerQT : public QObject
{
    Q_OBJECT

public:
    HTTPServerQT();
    virtual ~HTTPServerQT();
};

#endif // HTTPServerQT_H
