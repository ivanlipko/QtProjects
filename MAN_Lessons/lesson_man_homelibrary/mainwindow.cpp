#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

struct Book{
    QString title;
    QString author;
    unsigned int  pages;
    QDate date;
};

QList <Book> books;
unsigned int curBook;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curBook = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_add_clicked()
{
    Book b;

    b.title = ui->le_title->text();
    b.author = ui->le_author->text();
    b.pages = ui->le_pages->text().toUInt();
    b.date = ui->de_year->date();

    books.append(b);
}

void MainWindow::on_pb_show_next_clicked()
{
    // предусмотреть проверку диапазона
    curBook++;
    showBook(curBook);
}

void MainWindow::on_pb_show_prev_clicked()
{
    // предусмотреть проверку диапазона
    curBook--;
    showBook(curBook);
}

void MainWindow::showBook(unsigned int i)
{
    ui->le_title->setText(books[i].title);
    ui->le_author->setText(books[i].author);
    ui->le_pages->setText(QString::number(books[i].pages));
    ui->de_year->setDate(books[i].date);
}

void MainWindow::on_pb_saveFile_clicked()
{
    QFile f("data.txt");
    if(!f.open(QIODevice::WriteOnly))
        return;

    QTextStream ts(&f);
//    for (int i=0;;) {

//    }()
//    ts << books.;

    f.close();
}
