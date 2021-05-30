#include "network.h"

QString Network::getRcvdMessage() const
{
    return rcvdMessage_;
}

Network::Network()
{
    port_ = 5001;
}

bool Network::initServer(){
    serverSocket_ = new QTcpServer;
    if(!serverSocket_->listen(QHostAddress::AnyIPv4, port_)) {
        QMessageBox::critical(0, "Критическая ошибка", "Не запустил сервер");
        return false;
    }
    QObject::connect(serverSocket_, SIGNAL(newConnection()), this, SLOT(onConnection()));
    return true;
}

void Network::onConnection(){
    QTcpSocket *connectedClient = serverSocket_->nextPendingConnection();
    QObject::connect(connectedClient, SIGNAL(disconnected()),
                  connectedClient, SLOT(deleteLater()));

    QByteArray buffer;
    QDataStream streamBuffer(&buffer, QIODevice::WriteOnly);

    streamBuffer << QString("Сообщение получено. Ты подключился. Конец передачи");//"Client connected 1");//;
    connectedClient->write(buffer);

    qDebug() << connectedClient->localAddress()
             << connectedClient->localPort()
             << connectedClient->peerAddress()
             << connectedClient->peerName()
             << connectedClient->peerPort();
    connectedClient->disconnectFromHost();
}

void Network::onMsgRecieve(){
    QByteArray currentMessage;
    currentMessage = clientSocket_->readAll();

    qDebug() << currentMessage; // бинарный вид

    QString rcvdMessage(currentMessage);  // бинарный вид в строке - ерунда
    qDebug() << rcvdMessage;

    rcvdMessage.clear();
    QDataStream streamBuffer(&currentMessage, QIODevice::ReadOnly); // писали в поток, доставать тоже через поток, т.к. там ведь свой протокол сериализации
    streamBuffer >> rcvdMessage;
    qDebug() << rcvdMessage;

    rcvdMessage_ = rcvdMessage;
}

void Network::initAndConnectClient(){
    clientSocket_ = new QTcpSocket(this);
    connect(clientSocket_, SIGNAL(readyRead()), this, SLOT(onMsgRecieve()));
    //connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    clientSocket_->abort();
    clientSocket_->connectToHost(QHostAddress::LocalHost, port_);
}
