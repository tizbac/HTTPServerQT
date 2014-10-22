/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2014  Tiziano Bacocco <email>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 */

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QtCore/QObject>
#include <QTcpSocket>
#include <QStringList>
class HTTPClient : public QObject
{
    Q_OBJECT

public:
HTTPClient(QTcpSocket* sock);
virtual ~HTTPClient();
private:
  QTcpSocket * m_socket;
  QStringList buffer;
  void tryProcessingRequest();
  QString reqpath;
  QMap<QString,QString> headers;
private slots:
void incomingData();
public:
virtual void processGETRequest(QString reqpath, QMap< QString, QString > headers);
void sendResponse(QString code, QString desc, QString data, QString mimetype = QString("text/plain"));
void sendResponseBin(QString code, QString desc, QByteArray data, QString mimetype = QString("app/data"));
void sendResponseStreaming(QString code, QString desc,QString mimetype = QString("app/data"));
void writeLine(QString line,bool flush = false);
static QMap<QString,QString> parseCookies(QString cookiestr);
};

#endif // HTTPCLIENT_H
