#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QDebug"

// https://ru.wikipedia.org/wiki/ID3_(%D0%BC%D0%B5%D1%82%D0%B0%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5)

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

void MainWindow::on_pushButton_write_1_clicked()
{
    QFile file("data.bin");
    if (!file.open(QIODevice::WriteOnly)){
        qDebug() << "Error create file";
    }
    QDataStream stream(&file);
    stream << QStri ng( ui->lineEdit->text() );
    stream << qint16( ui->lineEdit_2->text().toInt() );
    stream << float( ui->lineEdit_3->text().toFloat() );
    file.close();
}

void MainWindow::on_pushButton_read_1_clicked()
{
    QFile file("data.bin");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Error open file";
    }
    QDataStream stream(&file);
    QString str;
    qint16 num1;
    float num2;
    stream >> str;
    stream >> num1;
    stream >> num2;
    file.close();

    ui->lineEdit_4->setText(str);
    ui->lineEdit_5->setText(QString::number(num1));
    ui->lineEdit_6->setText(QString::number(num2));
}

void MainWindow::on_pushButton_write_text_clicked()
{
    QFile file("data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Error create file";
    }
    QTextStream stream(&file);
    stream << ui->lineEdit->text() << '\n';
    stream << ui->lineEdit_2->text().toInt()  << '\n';
    stream << ui->lineEdit_3->text().toFloat()  << '\n';
    file.close();
}

void MainWindow::on_pushButton_read_text_clicked()
{
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error create file";
    }
    QTextStream stream(&file);
    ui->lineEdit_4->setText(stream.readLine());
    ui->lineEdit_5->setText(stream.readLine());
    ui->lineEdit_6->setText(stream.readLine());
    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    QFile file("music.mp3");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "Error open file";
    }
    file.seek(file.size()-128);

    QString string;
    string = QString( file.read(3) );
    qDebug() << string;
    QByteArray title;
    string = file.read(30);
    qDebug() << string;

//    QChar tag[3];
//    QChar title[30];
//    file.read(tag, 3)
//    file.read(title, 30);
//    qDebug() << tag;
//    qDebug() << title;

    file.close();
}
