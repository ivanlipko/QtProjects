#include "utils.h"
#include <QCryptographicHash>
#include <QFile>
#include <QDataStream>

const QString db_path = "db_users.bin";

QByteArray hashString(QString str){
    QByteArray byteStr;
    byteStr.append(str);

    return QCryptographicHash::hash( byteStr,  QCryptographicHash::Md5);
}

short addUser(QString email, QByteArray pass_hashed)
{
    QByteArray email_b;
    email_b.append(email);

    QFile f(db_path);
    if (!f.open(QIODevice::ReadOnly))
        return 10;  // error open

    QByteArray db_email;
    QByteArray db_pass;

    QDataStream ds(&f);
    while (!ds.atEnd()) {
        ds >> db_email >> db_pass;
        if(db_email == email_b) {
            f.close();
            return 1;  // email is used
        }
    }
    f.close();

    if (!f.open(QIODevice::WriteOnly | QIODevice::Append))
        return 11;  // error open

    ds.setDevice(&f);
    ds << email_b << pass_hashed;

    f.close();
    return 0;
}


short findUser(QString email, QByteArray pass_hashed){
    QByteArray email_b;
    email_b.append(email);

    QByteArray db_email;
    QByteArray db_pass;

    QFile f(db_path);
    if (!f.open(QIODevice::ReadOnly))
        return 10;

    QDataStream ds(&f);
    while (!ds.atEnd()) {
        ds >> db_email >> db_pass;
        if((db_email == email_b) && (db_pass == pass_hashed)) {
            f.close();
            return 0;
        }
    }

    f.close();
    return 1;
}
