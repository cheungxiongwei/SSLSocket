//
// Created by cheungxiongwei on 2022/9/5.
//

#include "ssl_server.h"
#include <qsslsocket.h>
#include <qsslcertificate.h>
#include <qsslkey.h>
#include <qnetworkproxy.h>
#include <qfileinfo.h>
#include <qfile.h>
#include <qdebug.h>

SSLServer::SSLServer(QObject *parent)
  : QTcpServer(parent) {
    qDebug("Using SSL library %s (%ld)", qPrintable(QSslSocket::sslLibraryVersionString()), QSslSocket::sslLibraryVersionNumber());

    auto fileByte = [](const QString &file)->auto{
        if(!QFileInfo::exists(file)){
            return QPair<bool,QByteArray>{false,QByteArray()};
        }

        QFile fs(file);
        if(!fs.open(QIODevice::ReadOnly)){
            return QPair<bool,QByteArray>{false,QByteArray()};
        }
        return QPair<bool,QByteArray>{true,fs.readAll()};
    };

    // [1]
    mSslConfig.setProtocol(QSsl::AnyProtocol);

    // [2] cert
    if(auto kv = fileByte("C:\\Users\\cheungxiongwei\\CLionProjects\\SSLSocket\\SSLServer\\cert.pem");kv.first){
        mSslConfig.setLocalCertificate(QSslCertificate(kv.second));
        qDebug() << "loading cert.pem succeed";
    }

    // [3] key
    if(auto kv = fileByte("C:\\Users\\cheungxiongwei\\CLionProjects\\SSLSocket\\SSLServer\\key.pem");kv.first){
        mSslConfig.setPrivateKey(QSslKey(kv.second,QSsl::Rsa));
        qDebug() << "loading key.pem succeed";
    }
}

SSLServer::SSLServer(quint16 port, QObject *parent)
  : SSLServer(parent) {
    qDebug("listen LocalHost:%d %s", port, listen(QHostAddress::LocalHost, port) ? "succeed" : "failed");
}

void SSLServer::incomingConnection(qintptr socketDescriptor) {
    auto *serverSocket = new QSslSocket;
    serverSocket->setProxy(QNetworkProxy::NoProxy);
    serverSocket->setSslConfiguration(mSslConfig);
    if(serverSocket->setSocketDescriptor(socketDescriptor)) {
        addPendingConnection(serverSocket);
        connect(serverSocket, &QSslSocket::encrypted, this,&SSLServer::encrypted);
        serverSocket->startServerEncryption();
    } else {
        delete serverSocket;
    }
}
