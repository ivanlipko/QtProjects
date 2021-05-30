#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QtNetwork>

class NetworkClient: public QObject
{
    Q_OBJECT

    QTcpSocket* client_;

public:
    NetworkClient();
    ~NetworkClient();
    void connectTo(QString address, quint16 port);
    void disconnectFromHost();
    void send(quint8 operation, qreal num1, qreal num2);

public slots:
    void onMsgRecieve();
    void onConnected();
    void onDisconnected();

signals:
    void msgRecieved(QByteArray msg);    
    void connected();
    void disconnected();
};

#endif // NETWORKCLIENT_H
