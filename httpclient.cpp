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

#include "httpclient.h"
#include <QSet>
#include <iostream>
#include <QtNetwork/qtcpsocket.h>

QSet<HTTPClient*> g_clients;
HTTPClient::HTTPClient(QTcpSocket * sock)
{
  g_clients.insert(this);
  m_socket = sock;
  connect(m_socket,SIGNAL(readyRead()),SLOT(incomingData()));
  connect(m_socket,SIGNAL(disconnected()),SLOT(deleteLater()));
}

HTTPClient::~HTTPClient()
{
  g_clients.remove(this);
}

void HTTPClient::incomingData()
{
  while ( m_socket->canReadLine() )
  {
    buffer.push_back(m_socket->readLine(1024));
//     std::cout << "!!" << buffer.last().toStdString() << std::endl;
    tryProcessingRequest();
    
    if ( buffer.length() > 128 )
    {
	m_socket->disconnectFromHost();
	return;
    }
  }
  
}

void HTTPClient::tryProcessingRequest()
{
  
  if ( buffer.length() > 0 )
  {
    QStringList tokens_req = buffer[0].split(" ");
    if ( tokens_req.size() == 3 )
    {
      if ( tokens_req[0] == "GET" )
      {
	reqpath = tokens_req[1];
	for ( int i = 1; i < buffer.length(); i++ )
	{
	  QString line = buffer[i].trimmed();
// 	  std::cout << line.length() << std::endl;
	  if ( line.length() > 0 )
	  {
	    QStringList htokens = line.split(":");
	    if ( htokens.length() >= 2 )
	    {
	      QString hname = htokens[0].trimmed();
	      htokens.pop_front();
	      headers.insert(hname,htokens.join(":").trimmed());
	    }
	      
	    
	    
	  }else{
	    processGETRequest(reqpath,headers);
	    reqpath = "";
	    headers.clear();
	    for ( int k = 0; k <= i; k++ )
	    {
	      buffer.pop_front();
	    }
	    return;
	  }
	}
	return;
      }
    }
    
  }else{
    return;
  }
  
  
  //BAD REQUEST
  sendResponse("400","Bad Request","Bad Request");
  
}
void HTTPClient::sendResponse(QString code,QString desc, QString data,QString mimetype)
{
  writeLine(QString("HTTP/1.1 ")+code+" "+desc);
  writeLine("Server: QtHTTPD");
  writeLine(QString("Content-Type: ")+mimetype);
  writeLine("Connection: close");
  writeLine(QString("Content-Length: %1").arg(data.length()));
  writeLine("");
  m_socket->write(data.toLatin1());
  m_socket->disconnectFromHost();
}
void HTTPClient::sendResponseBin(QString code, QString desc, QByteArray data, QString mimetype)
{
  writeLine(QString("HTTP/1.1 ")+code+" "+desc);
  writeLine("Server: QtHTTPD");
  writeLine(QString("Content-Type: ")+mimetype);
  writeLine("Connection: close");
  writeLine(QString("Content-Length: %1").arg(data.length()));
  writeLine("");
  m_socket->write(data);
  m_socket->disconnectFromHost();
}

void HTTPClient::sendResponseStreaming(QString code, QString desc, QString mimetype)
{
    writeLine(QString("HTTP/1.1 ")+code+" "+desc);
    writeLine("Server: QtHTTPD");
    writeLine(QString("Content-Type: ")+mimetype);
    writeLine("Connection: close");
    writeLine("");
}


void HTTPClient::writeLine(QString line, bool flush)
{
  QByteArray arr;
  arr.append(line.toUtf8());
  arr.append('\n');
  m_socket->write(arr);
  if ( flush )
      m_socket->flush();
}


void HTTPClient::processGETRequest(QString reqpath, QMap< QString, QString > headers)
{
  sendResponse("501","Not implemented","Non implementato");
}



QMap< QString, QString > HTTPClient::parseCookies(QString cookiestr)
{
  QStringList valuepairs = cookiestr.split(";");
  QMap<QString,QString> ret;
  for ( int i = 0; i < valuepairs.length(); i++ )
  {
    QString pair = valuepairs[i].trimmed();
    QStringList namevalue = pair.split("=");
    if ( namevalue.length() == 2 )
    {
      ret.insert(namevalue[0].trimmed(),namevalue[1].trimmed());
    }
  }
  return ret;
}

#include "httpclient.moc"
