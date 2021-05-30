#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setCamera(const QCameraInfo &cameraInfo);

private slots:
    void readyForCapture(bool ready);
    void on_takeImageButton_clicked();
    void processCapturedImage(int requestId, const QImage& img);

private:
    Ui::MainWindow *ui;

//    QScopedPointer<QCamera> m_camera;
    QCamera * camera;
    QCameraImageCapture *imageCapture;

};

#endif // MAINWINDOW_H
