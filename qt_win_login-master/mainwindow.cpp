#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->le_email->setValidator(new QRegularExpressionValidator(rx, this));

    QObject::connect(ui->le_email, SIGNAL(textChanged(QString)), this, SLOT(adjustTextColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adjustTextColor(){
    if(!ui->le_email->hasAcceptableInput())
        ui->le_email->setStyleSheet("QLineEdit { color: red;}");
    else
        ui->le_email->setStyleSheet("QLineEdit { color: black;}");
}

void MainWindow::on_pb_login_clicked()
{
    QString email = ui->le_email->text();
    QString pass = ui->le_pass->text();
//    bool isEmailValid = validateEmail(email);
    bool isEmailValid = ui->le_email->hasAcceptableInput();

    if (isEmailValid) {
        QByteArray hash = hashString(pass);
        short userExistHandle = findUser(email, hash);

        switch (userExistHandle) {
        case 0:  // authorize it
            QMessageBox::information(this,"Signed in","You are in the db!");
            break;
        case 1:  // user not found
            QMessageBox::warning(this,"No user","You are NOT in the db or password is incorrect!");
            break;
        case 10:  // file open error
            QMessageBox::critical(this,"Critical","Can't open file");
            break;
        }
    } else
        QMessageBox::warning(this,"Error","Email is not valid!");
}

void MainWindow::on_pb_noAccount_clicked()
{
    regWin = new RegistrationDialog;
    regWin->exec();
}

void MainWindow::on_le_pass_returnPressed()
{
    on_pb_login_clicked();
}
