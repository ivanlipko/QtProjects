#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QByteArray>

QByteArray hashString(QString str);
short addUser(QString email, QByteArray pass_hashed);
short findUser(QString email, QByteArray pass_hashed);

#endif // UTILS_H
