#include "network.h"

Network::Network(QObject *parent) : QObject(parent)
{

}

Network::~Network()
{
    delete socketIn;
    delete socketOut;
}

void Network::initSockets(quint16 portIn, QHostAddress remoteAddress, quint16 remotePort)
{
    portIn_ = portIn;
    remotePort_ = remotePort;
    remoteAddress_ = remoteAddress;

    socketIn = new QUdpSocket(this);
    bool isBind = socketIn->bind(QHostAddress::AnyIPv4, portIn_);
    connect(socketIn, SIGNAL(readyRead()), this, SLOT(readIncoming()));

    qDebug() << "Network::initSockets" << isBind;

    socketOut = new QUdpSocket(this);
    socketOut->connectToHost(remoteAddress_, remotePort_);
    connect(socketOut, SIGNAL(hostFound()), this, SLOT(onHostFound()));
    // notify of reading
}

void Network::readIncoming()
{
    qDebug() << "Network::readIncoming " << "in";
    while (socketIn->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socketIn->pendingDatagramSize());
        socketIn->readDatagram(datagram.data(), datagram.size(), &remoteAddress_, &remotePort_);

        processTheDatagram(datagram);
        qDebug() << "Network::readIncoming " << datagram;
    }
}

void Network::processTheDatagram(QByteArray datagram)
{
    QDataStream stream(&datagram, QIODevice::ReadOnly);
    quint8 operation;
    quint32 data;
    stream >> operation;
    stream >> data;

    qDebug() << "Network::processTheDatagram " << operation << ", " << data;
    emit(readDatagram(operation, data));
}

void Network::send(quint8 operation, quint32 data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << quint8(operation) << quint32 (data);
    socketOut->writeDatagram(datagram, remoteAddress_, remotePort_);
    qDebug() << "Network::send " << operation << ", " << data;
}

void Network::onHostFound()
{
    qDebug() << "Network::onHostFound";
}

