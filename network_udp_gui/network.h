#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QtNetwork>

class Network : public QObject
{
    Q_OBJECT

    QUdpSocket* socketIn;
    QUdpSocket* socketOut;

    quint16 portIn_;
    quint16 remotePort_;
    QHostAddress remoteAddress_;

public:
    explicit Network(QObject *parent = 0);
    ~Network();

    void initSockets(quint16 portIn, QHostAddress remoteAddress, quint16 remotePort);
    void processTheDatagram(QByteArray datagram);
    void send(quint8 operation, quint32 data);


signals:
    void readDatagram(quint8 operation, quint32 data);

public slots:
    void readIncoming();
    void onHostFound();
};

#endif // NETWORK_H
