#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QMessageBox>
#include "utils.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->le_email->setValidator(new QRegularExpressionValidator(rx, this));

    QObject::connect(ui->le_email, SIGNAL(textChanged(QString)), this, SLOT(adjustTextColor()));
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::adjustTextColor(){
    if(!ui->le_email->hasAcceptableInput())
        ui->le_email->setStyleSheet("QLineEdit { color: red;}");
    else
        ui->le_email->setStyleSheet("QLineEdit { color: black;}");
}

void RegistrationDialog::on_pb_add_user_clicked()
{
    QString email = ui->le_email->text();
    QString pass = ui->le_pass->text();
    QString pass2 = ui->le_pass_dupl->text();

    if (pass == pass2) {
        bool isEmailValid = validateEmail(email);
        if (isEmailValid) {
            QByteArray hash = hashString(pass);
            short userAddedHandle = addUser(email, hash);

            switch (userAddedHandle) {
            case 0:  // added
                QMessageBox::information(this,"Signed up","Welcome to Data Base! You are added.");
                break;
            case 1:  // user exist
                QMessageBox::information(this,"Email exist","Email is exist, add new email!");
                break;
            case 10:;  // file open error
            case 11:  // file open error
                QMessageBox::critical(this,"Critical","Can't open file");
                break;
            }
        } else
            QMessageBox::critical(this, "Critical", "Email is not valid!");

    } else {
        QMessageBox::warning(this, "Warning", "Check your passwords, they must be equal.");
    }
}

