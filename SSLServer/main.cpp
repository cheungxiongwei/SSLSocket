#include <QCoreApplication>
#include <QDebug>
#include "ssl_server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    SSLServer app(8888);
    QObject::connect(&app, &SSLServer::encrypted, &a, [] { qDebug() << " :encrypted"; });
    return QCoreApplication::exec();
}
