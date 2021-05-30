#ifndef TURWIDGET_H
#define TURWIDGET_H

#include <QWidget>

namespace Ui {
    class TurWidget;
}

class TurWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TurWidget(QWidget *parent = 0);
    ~TurWidget();

private slots:
    void on_tableWidgetFights_cellPressed(int row, int column);

    void on_tableWidgetFights_cellChanged(int row, int column);

    void on_tableWidgetUsers_cellChanged(int row, int column);


    void on_pushButtonAddUser_clicked();

    void on_pushButtonDeleteUser_clicked();

private:
    Ui::TurWidget *ui;
};

#endif // TURWIDGET_H
