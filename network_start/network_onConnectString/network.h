#ifndef NETWORK_H
#define NETWORK_H
#include <QtNetwork/QtNetwork>
#include <QMessageBox>

class Network: public QObject
{
    Q_OBJECT

    quint16 port_;
    QTcpServer* serverSocket_;
    QTcpSocket* clientSocket_;
    QString rcvdMessage_;

public:
    Network();
    bool initServer();
    void initAndConnectClient();

    QString getRcvdMessage() const;

private slots:
    void onConnection();
    void onMsgRecieve();
};

#endif // NETWORK_H
