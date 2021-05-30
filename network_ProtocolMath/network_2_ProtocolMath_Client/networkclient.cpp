#include "networkclient.h"

NetworkClient::NetworkClient()
{

}

NetworkClient::~NetworkClient()
{
    client_->disconnectFromHost();
    delete client_;
}

void NetworkClient::connectTo(QString address, quint16 port){
    client_ = new QTcpSocket(this);
    connect(client_, SIGNAL(readyRead()), this, SLOT(onMsgRecieve()));
    connect(client_, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(client_, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    //connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    client_->abort();
    client_->connectToHost(address, port);
}

void NetworkClient::onMsgRecieve(){
    QByteArray binMessage;
    binMessage = client_->readAll();
    emit(msgRecieved(binMessage));
}

void NetworkClient::onConnected()
{
    emit(connected());
}

void NetworkClient::onDisconnected(){
    emit(disconnected());
}

void NetworkClient::send(quint8 operation, qreal num1, qreal num2){
    QDataStream streamSocket(client_);
    streamSocket << quint8(operation) << qreal(num1) << qreal(num2);
}

void NetworkClient::disconnectFromHost(){
    client_->disconnectFromHost();
}
