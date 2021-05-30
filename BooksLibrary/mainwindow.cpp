#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDataStream>

struct Book{
    QString title;
    QString author;
    qint16 year;
    bool isBook;
};

QFile file("file.dat");
quint8 curent_page = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (file.exists()) {
        file.open(QIODevice::ReadWrite);   // open file to READ and WRITE
        QDataStream in(&file);
        Book book;
        in  >> book.author
            >> book.title
            >> book.year
            >> book.isBook;

        ui->lineEdit_author->setText(book.author);
        ui->lineEdit_title->setText(book.title);
        ui->lineEdit_year->setText( QString::number(book.year) );
        ui->radioButton_isbook->setChecked(book.isBook);
        ui->radioButton_isjourn->setChecked(book.isBook);
    } else {
        file.open(QIODevice::WriteOnly);   // create file
        file.close();
        file.open(QIODevice::ReadWrite);   // open file to READ and WRITE
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    file.close();   // close file
}

void MainWindow::on_pushButton_addBook_clicked()
{
    QDataStream out(&file);
    Book book;
    book.author = ui->lineEdit_author_in->text();
    book.title = ui->lineEdit_titl_in->text();
    book.year= ui->lineEdit_year_in->text().toInt();
    book.isBook = ui->radioButton_book_in->isChecked();

//    QByteArray b;
//    b.append(book.author);
//    b.append(book.title);
//    b.append(book.year);
//    b.append(book.isBook);
//    out << b;

    out << book.author
       << book.title
       << book.year
       << book.isBook;
}

void MainWindow::on_pushButton_show_next_clicked()
{
    QDataStream in(&file);
    Book book;
    in  >> book.author
            >> book.title
            >> book.year
            >> book.isBook;

    ui->lineEdit_author->setText(book.author);
    ui->lineEdit_title->setText(book.title);
    ui->lineEdit_year->setText( QString::number(book.year) );
    ui->radioButton_isbook->setChecked(book.isBook);
    ui->radioButton_isjourn->setChecked(book.isBook);
}

void MainWindow::on_pushButton_clicked()
{
    if(curent_page == 0)
        curent_page = 1;
    else
        curent_page = 0;
    ui->stackedWidget->setCurrentIndex(curent_page);
}

void MainWindow::on_pushButton_show_prev_clicked()
{
    QDataStream in(&file);
//    qint64 temp = file.pos();

    if (file.seek(file.pos() - 64))    {
        Book book;
        in  >> book.author
                >> book.title
                >> book.year
                >> book.isBook;

        ui->lineEdit_author->setText(book.author);
        ui->lineEdit_title->setText(book.title);
        ui->lineEdit_year->setText( QString::number(book.year) );
        ui->radioButton_isbook->setChecked(book.isBook);
        ui->radioButton_isjourn->setChecked(book.isBook);
    }
}
