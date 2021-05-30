#include "networkserver.h"

/*
    Protocol:
        operation   - quint8;
            1 - connected
            2 - +
            3 - -
            4 - *
            5 - /
            6 - =, result
        1 number, result    - qreal;
        2 number            - qreal;
*/

QList<QTcpSocket *> NetworkServer::clients() const
{
    return clients_;
}

NetworkServer::NetworkServer()
{
    port_ = 5001;
}

NetworkServer::~NetworkServer()
{
    QTcpSocket* tempSock;
    while (!clients_.isEmpty()) {
        tempSock = clients_.takeFirst();
        tempSock->disconnectFromHost();     // ???
        delete tempSock;
    }
    serverSocket_->close();
}

bool NetworkServer::initServer(){
    serverSocket_ = new QTcpServer;
    if(!serverSocket_->listen(QHostAddress::AnyIPv4, port_)) {
        QMessageBox::critical(0, "Критическая ошибка", "Не запустил сервер");
        return false;
    }
    QObject::connect(serverSocket_, SIGNAL(newConnection()), this, SLOT(onConnection()));
    return true;
}

void NetworkServer::onConnection(){
    while(serverSocket_->hasPendingConnections()) {
        QTcpSocket* connectedClient = serverSocket_->nextPendingConnection();
        clients_.append(connectedClient);
        QObject::connect(connectedClient, SIGNAL(disconnected()),
                         this, SLOT(onDisconnect()));      // deleteLater() ?
        QObject::connect(connectedClient, SIGNAL(readyRead()),
                         this, SLOT(manageMessage()));

        QByteArray buffer;
        QDataStream streamBuffer(&buffer, QIODevice::WriteOnly);
        streamBuffer << quint8(1) << qreal(0.0) << qreal (0.0);
        connectedClient->write(buffer);

        emit(newConnection());
    }
}

void NetworkServer::onDisconnect(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    bool isTemp = clients_.removeOne(clientSocket);
    qDebug() << clientSocket << isTemp;
}

void NetworkServer::manageMessage(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    QByteArray msg;
    msg = clientSocket->readAll();
    QDataStream streamSocket(clientSocket);

    quint8 operation;
    qreal num1, num2, result;

    QDataStream streamBuffer(&msg, QIODevice::ReadOnly);
    streamBuffer >> operation;
    streamBuffer >> num1;
    streamBuffer >> num2;

    switch (operation) {
    case 2:
        result = num1 + num2;
        break;
    case 3:
        result = num1 - num2;
        break;
    case 4:
        result = num1 * num2;
        break;
    case 5:
        result = num1 / num2;
        break;
    default:
        break;
    }

    streamSocket << quint8(6) << qreal(result) << qreal(0.0);
}
