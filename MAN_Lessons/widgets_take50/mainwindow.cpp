#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"



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

void MainWindow::removeItemWidget(QString str){
    QList<QListWidgetItem *> list;
    list = ui->listWidget_selected->findItems(str, Qt::MatchContains);
//    ui->label_win->setText(list.at(0)->text());
    delete list.at(0);
//        ui->listWidget_selected->removeItemWidget(list.at(0)); - не работает
}

void MainWindow::on_checkBox25_clicked(bool checked)
{
    if(checked){
        gAdd(25);
        ui->listWidget_selected->addItem("25");
    }
    else {
        gRemove(25);
        removeItemWidget("25");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox27_clicked(bool checked)
{
    if(checked){
        gAdd(27);
        ui->listWidget_selected->addItem("27");
    }
    else {
        gRemove(27);
        removeItemWidget("27");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox3_clicked(bool checked)
{
    if(checked){
        gAdd(3);
        ui->listWidget_selected->addItem("3");
    }
    else {
        gRemove(3);
        removeItemWidget("3");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox12_clicked(bool checked)
{
    if(checked){
        gAdd(12);
        ui->listWidget_selected->addItem("12");
    }
    else {
        gRemove(12);
        removeItemWidget("12");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox6_clicked(bool checked)
{
    if(checked){
        gAdd(6);
        ui->listWidget_selected->addItem("6");
    }
    else {
        gRemove(6);
        removeItemWidget("6");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox15_clicked(bool checked)
{
    if(checked){
        gAdd(15);
        ui->listWidget_selected->addItem("15");
    }
    else {
        gRemove(15);
        removeItemWidget("15");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox9_clicked(bool checked)
{
    if(checked){
        gAdd(9);
        ui->listWidget_selected->addItem("9");
    }
    else {
        gRemove(9);
        removeItemWidget("9");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox30_clicked(bool checked)
{
    if(checked){
        gAdd(30);
        ui->listWidget_selected->addItem("30");
    }
    else {
        gRemove(30);
        removeItemWidget("30");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox21_clicked(bool checked)
{
    if(checked){
        gAdd(21);
        ui->listWidget_selected->addItem("21");
    }
    else {
        gRemove(21);
        removeItemWidget("21");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}

void MainWindow::on_checkBox19_clicked(bool checked)
{
    if(checked){
        gAdd(19);
        ui->listWidget_selected->addItem("19");
    }
    else {
        gRemove(19);
        removeItemWidget("19");
    }
    if (gIs50())
        ui->label_win->setText("You win!");
    else ui->label_win->setText(QString::number(gGetPoints()));
}
