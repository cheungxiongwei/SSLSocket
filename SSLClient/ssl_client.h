//
// Created by cheungxiongwei on 2022/9/5.
//

#ifndef SSLSOCKET_SSL_CLIENT_H
#define SSLSOCKET_SSL_CLIENT_H

#include "qsslsocket.h"
#include <qsslconfiguration.h>

class SSLClient : public QSslSocket
{
    Q_OBJECT

public:
    explicit SSLClient(QObject *parent = nullptr);
    ~SSLClient();

private:
    QSslConfiguration mSslConfig;
};

#endif  //SSLSOCKET_SSL_CLIENT_H
