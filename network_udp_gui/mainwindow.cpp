#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData(quint8 operation, quint32 data)
{
    qDebug() << "ui.readData " << operation << ", " << data;
    ui->textEdit->append("<< " + QString::number(operation) + ", " + QString::number(data));
}

void MainWindow::on_pushButton_clicked()
{
    net = new Network;
    net->initSockets(ui->lineEdit_localPort->text().toInt(), QHostAddress(ui->lineEdit_remoteAddress->text()),
                     ui->lineEdit_remotePort->text().toInt());
}

void MainWindow::on_pushButton_3_clicked()
{
    delete net;
}

void MainWindow::on_pushButton_2_clicked()
{
    net->send(ui->lineEdit_operation->text().toInt(), ui->lineEdit_data->text().toInt());
}
