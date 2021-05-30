#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "achivementtimer.h"
#include "ultimate.h"
#include "QMovie"
#include "QTime"
#include "QSoundEffect"
#include "QGraphicsScene"
#include "QPixmap"

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
    void on_pushButton_clicked();
    void on_pushButton_BuyAchive_clicked();

    void onUpdateGui();
    void onUpdateLevel();

    void on_pushButton_2_clicked();

    void on_pushButton_BuyAchive_pressed();

    void on_pushButton_BuyAchive_released();

private:
    Ui::MainWindow *ui;

    AchivementTimer *_achiveThread;
    QMovie *_movie;

    short _lastLevel;
    QTime _lastTime;
    bool _isGameRun;

    QGraphicsScene *scn;
    QSoundEffect * sfxLevelup[3];
    QSoundEffect * sfxClick[2];
    QPixmap * pix;
};

#endif // MAINWINDOW_H
