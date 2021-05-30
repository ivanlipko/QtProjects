#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSql>
#include <QDebug>
#include <QMessageBox>

QSqlDatabase db;

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

void MainWindow::on_pushButtonRunSqlQuery_clicked()
{
    QSqlQuery query("topChatDB");
    QString queryString = ui->textEditSqlText->document()->toPlainText();
//    QStringList queryStringL = queryString.section(';');
//    qD

    ui->textEditSqlText->clear();

    query.exec(queryString);

    if (!query.lastError().type()){
        ui->textEditSq_history->append(queryString);
    } else {
        qDebug() << query.lastError().text();
        ui->textEditSq_history->append(query.lastError().text());
    }

    int querySize = query.record().count();
    qDebug() << querySize;

    QTextDocument * textDoc = ui->textEditSqlResultText->document();
    QString queryValue;
    while (query.next()) {
        for (int i=0; i<querySize; i++) {
            queryValue = query.value(i).toString();
            textDoc->setPlainText(textDoc->toPlainText() + queryValue + "\t");
        }
        textDoc->setPlainText(textDoc->toPlainText() + "\r\n");
    }
}

void MainWindow::on_pushButton_clicked()
{
    db.close();
    qDebug() << db.lastError().text();
}

/*
create table data
(
Login string,
Password string,
Status string
);

drop table data
select * from data

insert into data (Login, Password, Status) values ("DareDevil", "51770123", "admin")
*/


/*
create table brand (
 idB int,
 name char(20),
 age int,
 country char(20)
)

create table techType (
 idT int,
 idB int,
 type char(3)
)

create table mboards (
 idMb int,
 type char(3),
 socket char(30),
 ram int,
 size int
)

insert into brand (idB, name, age, country) values (1, "Lenovo", 10, "ENG")
insert into brand (idB, name, age, country) values (2, "IBM", 10, "USA")
select * from brand

insert into techType (idT, idB, type) values (1, 1, "MBD"), (2, 2, "CPU"), (3, 1, "GPU")
select * from techType

insert into mboards (idMb, type, socket, ram, size) values (1, "MBD", 775, 4, 1), (1, "MBD", 775, 8, 1), (1, "MBD", 775, 16, 1)
select * from mboards

select * from mboards
where techType.idB in (
select idB from brand
where brand.name="Lenovo"
)
*/

void MainWindow::on_pb_Open_db_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << db.drivers();

    db.setDatabaseName( QCoreApplication::applicationDirPath() + "/" ); // topChatDB
    qDebug() << db.databaseName();

    bool dbConnected = db.open();

    if (!dbConnected) {
        QMessageBox::critical(
             this,
             QObject::tr("Database Error"),
             db.lastError().text());
        qDebug() << db.lastError().text();
    }

    //db.close();
}
