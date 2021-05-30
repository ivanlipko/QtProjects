#include "network.h"
#include <QMessageBox>

Network::Network()
{

}

Network::~Network()
{
    delete server_;
    delete client_;
}

void Network::runServer(quint16 port){
    server_ = new QTcpServer;

    if(! server_->listen(QHostAddress::AnyIPv4, port)){
        QMessageBox::critical(0, "Ошибка", "Сервер не запущен");
        return;
    }
    QObject::connect(server_, SIGNAL(newConnection()),
                     this, SLOT(onConnection()) );
}

void Network::onConnection(){
    QTcpSocket* client;
    client = server_->nextPendingConnection();
    qDebug() << client->peerAddress()
             << client->peerPort()
             << client->peerName();
    QDataStream stream(client);
    stream << QString("Привет, ты на сервере!");
    client->disconnectFromHost();
    // float, qint8
}

void Network::connectTo(QString address, quint16 port){
    client_ = new QTcpSocket;
    client_->connectToHost(address, port);
    QObject::connect(client_, SIGNAL(readyRead()),
                     this, SLOT(onRead()) );
}

void Network::onRead(){
    QByteArray binData;
    binData = client_->readAll();
    QDataStream stream(binData);
    QString str;
    stream >> str;
    qDebug() << str << binData;
}
