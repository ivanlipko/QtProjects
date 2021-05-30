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
    ui->label_output->setText( ui->lineEdit_input->text() );
}

void MainWindow::on_lineEdit_input_textEdited(const QString &arg1)
{
    ui->label_output->setText(arg1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText( ui->lineEdit->text() + ", так держать!" );
}
