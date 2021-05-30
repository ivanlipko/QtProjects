#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client_ = new NetworkClient;
    QObject::connect(client_, SIGNAL(msgRecieved(QByteArray)),
                     this, SLOT(onMsgRecieved(QByteArray)));
    QObject::connect(client_, SIGNAL(connected()),
                     this, SLOT(onConnected()));
    QObject::connect(client_, SIGNAL(disconnected()),
                     this, SLOT(onDisconnected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    client_->connectTo(ui->lineEdit_address->text(), ui->lineEdit_port->text().toInt());
}

void MainWindow::onMsgRecieved(QByteArray msg){
    quint8 operation;
    qreal num1, num2;

    QDataStream streamBuffer(&msg, QIODevice::ReadOnly);
    streamBuffer >> operation;
    streamBuffer >> num1;
    streamBuffer >> num2;

    switch (operation) {
    case 1:
        ui->label_isConnected->setText("Connected");
        ui->te_log->append("Connected _ sended");
        break;
    case 6:
        ui->lineEdit_result->setText(QString::number(num1));
        break;
    default:
        break;
    }
}

void MainWindow::onConnected(){
    ui->te_log->append("Connected");
}

void MainWindow::onDisconnected(){
    ui->te_log->append("Disconnected");
}

void MainWindow::on_pushButton_2_clicked()
{
    client_->send(2, ui->lineEdit_num1->text().toFloat(), ui->lineEdit_num2->text().toFloat());
}

void MainWindow::on_pushButton_3_clicked()
{
    client_->send(3, ui->lineEdit_num1->text().toFloat(), ui->lineEdit_num2->text().toFloat());
}

void MainWindow::on_pushButton_4_clicked()
{
    client_->send(4, ui->lineEdit_num1->text().toFloat(), ui->lineEdit_num2->text().toFloat());
}

void MainWindow::on_pushButton_5_clicked()
{
    client_->send(5, ui->lineEdit_num1->text().toFloat(), ui->lineEdit_num2->text().toFloat());
}

void MainWindow::on_pushButton_6_clicked()
{
    client_->disconnectFromHost();
}
