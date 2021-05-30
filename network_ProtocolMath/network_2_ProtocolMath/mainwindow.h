#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    NetworkServer* server_;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void onConnection();
};

#endif // MAINWINDOW_H
