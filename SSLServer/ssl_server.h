//
// Created by cheungxiongwei on 2022/9/5.
//

#ifndef SSLSOCKET_SSL_SERVER_H
#define SSLSOCKET_SSL_SERVER_H

#include <qtcpserver.h>
#include <qsslconfiguration.h>

class SSLServer : public QTcpServer
{
    Q_OBJECT

public:
    SSLServer(QObject *parent = nullptr);

    SSLServer(quint16 port, QObject *parent = nullptr);
signals:
    void encrypted();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QSslConfiguration mSslConfig;
};
#endif  //SSLSOCKET_SSL_SERVER_H
