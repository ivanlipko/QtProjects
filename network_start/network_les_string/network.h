#ifndef NETWORK_H
#define NETWORK_H

#include <QtNetwork>

class Network: public QObject
{
    Q_OBJECT

    QTcpServer* server_;
    QTcpSocket* client_;

public:
    Network();
    ~Network();

    void runServer(quint16 port);
    void connectTo(QString address, quint16 port);

public slots:
    void onConnection();
    void onRead();

};

#endif // NETWORK_H
