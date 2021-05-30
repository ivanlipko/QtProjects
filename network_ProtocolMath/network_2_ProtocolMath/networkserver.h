#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QtNetwork>
#include <QMessageBox>
#include <QList>

class NetworkServer: public QObject
{
    Q_OBJECT

    quint16 port_;
    QTcpServer* serverSocket_;
    QList <QTcpSocket*> clients_;

public:
    NetworkServer();
    ~NetworkServer();
    bool initServer();

    QList<QTcpSocket *> clients() const;

private slots:
    void onConnection();
    void onDisconnect();
    void manageMessage();

signals:
    void newConnection();
};

#endif // NETWORKSERVER_H
