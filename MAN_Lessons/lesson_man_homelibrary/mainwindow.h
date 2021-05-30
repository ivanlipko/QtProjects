#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_add_clicked();

    void on_pb_show_next_clicked();

    void on_pb_show_prev_clicked();

    void on_pb_saveFile_clicked();

private:
    Ui::MainWindow *ui;

    void showBook(unsigned int i);
};
#endif // MAINWINDOW_H
