#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registrationdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_login_clicked();

    void on_pb_noAccount_clicked();

    void on_le_pass_returnPressed();

    void adjustTextColor();

private:
    Ui::MainWindow *ui;
    RegistrationDialog * regWin;

};

#endif // MAINWINDOW_H
