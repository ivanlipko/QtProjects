#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createChild()
{
    mdiWindow * childWindow = new mdiWindow(mdiArea);
    childWindow->setAttribute(Qt::WA_DeleteOnClose);
    mdiArea->addSubWindow(childWindow);

    childWindow->show();
    return;
}
