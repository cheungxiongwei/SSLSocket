#include <QCoreApplication>
#include <QDebug>
#include "ssl_client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    SSLClient sslSocket;
    QObject::connect(&sslSocket, &SSLClient::peerVerifyError, &a, [] {
        // if receive an peerVerifyError error can here disconnectFromHost
        qDebug() << " :peerVerifyError";
    });
    QObject::connect(&sslSocket, QOverload<const QList<QSslError> &>::of(&SSLClient::sslErrors), &a, [&](const QList<QSslError> &errors) {
        qDebug() << " :sslErrors";
        for(auto &err: errors) {
            // The certificate is self-signed, and untrusted
            if(err.error() == QSslError::SelfSignedCertificate) {
                sslSocket.ignoreSslErrors();
            }
        }
    });
    QObject::connect(&sslSocket, &SSLClient::encrypted, &a, [] { qDebug() << " :encrypted"; });
    sslSocket.connectToHostEncrypted("localhost", 8888);
    return QCoreApplication::exec();
}
