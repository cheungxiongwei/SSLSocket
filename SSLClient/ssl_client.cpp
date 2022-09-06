//
// Created by cheungxiongwei on 2022/9/5.
//

#include "ssl_client.h"
#include <qsslcertificate.h>
#include <qsslkey.h>

SSLClient::SSLClient(QObject *parent)
  : QSslSocket(parent) {
    mSslConfig.setProtocol(QSsl::AnyProtocol);
    auto cert = QSslCertificate::fromPath(R"(C:\Users\cheungxiongwei\CLionProjects\SSLSocket\SSLClient\cert.pem)");
    mSslConfig.setCaCertificates(cert);
    setSslConfiguration(mSslConfig);
}

SSLClient::~SSLClient() {}
