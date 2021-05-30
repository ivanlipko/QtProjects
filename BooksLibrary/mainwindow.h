#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_addBook_clicked();

    void on_pushButton_show_next_clicked();

    void on_pushButton_clicked();

    void on_pushButton_show_prev_clicked();

private:
    Ui::MainWindow *ui;

//    void showItem();
};

#endif // MAINWINDOW_H
