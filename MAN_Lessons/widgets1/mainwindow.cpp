#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mathAdd.h"

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

void MainWindow::on_pushButton_clicked()
{
    float a, b;
    a = ui->lineEdit->text().toFloat();
    b = ui->lineEdit_2->text().toFloat();

    ui->label->setText("Площадь = "
          + QString::number(getSquare(a,b)));
    ui->label_2->setText("Perimetr = "
         + QString::number(getPerimetr(a,b)));
}


