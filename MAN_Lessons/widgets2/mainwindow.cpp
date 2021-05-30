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

void MainWindow::on_pushButton_clicked()
{
    // приращение текста
    ui->label->setText( ui->label->text() + ui->lineEdit->text() );
}


void MainWindow::on_pushButton_2_clicked()
{
    int num = 0;
    num = ui->lineEdit->text().toInt();
    ui->label_numbers->clear();
    if(ui->checkBox->isChecked()){
        for(int i=1; i<=num; i++)
            ui->label_numbers->setText(
                        ui->label_numbers->text() + " " +
                        QString::number(i));
    } else {
        for(int i=num; i>0; i--)
            ui->label_numbers->setText(
                        ui->label_numbers->text() + " " +
                        QString::number(i));
        /*
            for(int i=0; i<=num; i++)
                ... QString::number(num-i)
        */
    }
}
