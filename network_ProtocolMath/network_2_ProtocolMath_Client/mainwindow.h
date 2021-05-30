#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NetworkClient* client_;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onMsgRecieved(QByteArray msg);
    void onConnected();
    void onDisconnected();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
