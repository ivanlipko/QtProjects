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
    void on_checkBox25_clicked(bool checked);

    void on_checkBox27_clicked(bool checked);

    void on_checkBox3_clicked(bool checked);

    void on_checkBox12_clicked(bool checked);

    void on_checkBox6_clicked(bool checked);

    void on_checkBox15_clicked(bool checked);

    void on_checkBox9_clicked(bool checked);

    void on_checkBox30_clicked(bool checked);

    void on_checkBox21_clicked(bool checked);

    void on_checkBox19_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    void removeItemWidget(QString str);
};

#endif // MAINWINDOW_H
