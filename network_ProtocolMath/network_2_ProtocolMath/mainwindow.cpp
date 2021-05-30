#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server_ = new NetworkServer;
    QObject::connect(server_, SIGNAL(newConnection()), this, SLOT(onConnection()));
    server_->initServer();
}

MainWindow::~MainWindow()
{
    delete server_;

    delete ui;
}

void MainWindow::onConnection(){
    QString msg = "New connection from " + server_->clients().last()->peerAddress().toString();
    ui->textEdit->append(msg);
}
