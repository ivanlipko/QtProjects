#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // List available cameras
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        QString info;
        info.append(cameraInfo.deviceName());
        info.append(" " +  cameraInfo.description());
        ui->textEdit->append(info);
    }

    setCamera(QCameraInfo::defaultCamera());
}

void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    camera = new QCamera(cameraInfo);
    camera->setViewfinder(ui->widget_view);

    imageCapture = new QCameraImageCapture(camera);
    connect(imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(readyForCapture(bool)));
    connect(imageCapture, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(processCapturedImage(int , const QImage&)));

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start(); // Viewfinder frames start flowing
}

void MainWindow::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void MainWindow::processCapturedImage(int requestId, const QImage& img)
{
    img.save("image.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;

    delete camera;
    delete imageCapture;
}

void MainWindow::on_takeImageButton_clicked()
{
    //on half pressed shutter button
    camera->searchAndLock();

    //on shutter button pressed
    imageCapture->capture();

    //on shutter button released
    camera->unlock();
         //on shutter button pressed
//         imageCapture->capture();
}
