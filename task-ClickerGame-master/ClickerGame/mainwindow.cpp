#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include "QMessageBox"
//#include "QFileDialog"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _lastLevel = 0;

    _achiveThread = new AchivementTimer();
    connect(_achiveThread, SIGNAL(updateGUI()), this, SLOT(onUpdateGui()));
    connect(_achiveThread, SIGNAL(updateLevel()), this, SLOT(onUpdateLevel()));
    connect(_achiveThread, &AchivementTimer::finished, _achiveThread, &QObject::deleteLater);

    _movie = new QMovie("cat.gif", "GIF");
    _movie->setCacheMode(QMovie::CacheAll);

    ui->pushButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    ui->pushButton_BuyAchive->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

    bool isVisibile = false;
    ui->label->setVisible(isVisibile);
    ui->label_2->setVisible(isVisibile);
    ui->label_3->setVisible(isVisibile);
    ui->label_AchiveLevel->setVisible(isVisibile);
    ui->label_AddMoneyIndicator->setVisible(isVisibile);
    ui->label_AddPointAchiveIndecator->setVisible(isVisibile);
    ui->label_curClickSlide->setVisible(isVisibile);
    ui->label_gameEnd->setVisible(isVisibile);
    ui->label_Level->setVisible(isVisibile);
    ui->label_Money->setVisible(isVisibile);
    ui->label_nextLevelExpIndicator->setVisible(isVisibile);
    ui->label_picture->setVisible(isVisibile);
    ui->pushButton->setVisible(isVisibile);
    ui->pushButton_2->setVisible(!isVisibile);
    ui->pushButton_BuyAchive->setVisible(isVisibile);
    ui->lcdNumber_myGameTime->setVisible(isVisibile);
    ui->graphicsView->setVisible(isVisibile);

    // цвет циферблата
    QPalette palette = ui->lcdNumber_myGameTime->palette();
//    # foreground color
    palette.setColor(palette.WindowText, QColor(245, 245, 55));
//    # background color
    palette.setColor(palette.Background, QColor(0, 170, 55));
//    # "light" border
    palette.setColor(palette.Light, QColor(255, 0, 0));
//    # "dark" border
    palette.setColor(palette.Dark, QColor(0, 255, 0));
//    # set the palette
    ui->lcdNumber_myGameTime->setPalette(palette);

    scn  = new QGraphicsScene( ui->graphicsView );
    scn->setSceneRect( ui->graphicsView->rect() );
    ui->graphicsView->setScene( scn );
    ui->graphicsView->setStyleSheet("background-color: transparent;");
    pix = new QPixmap("./pics/1.png");

    qsrand(123);

    for (short i=0; i<2; i++) {
        sfxClick[i] = new QSoundEffect(this);
        // load files from "/exeDir/sound/click-0X.wav"
        sfxClick[i]->setSource(QUrl::fromLocalFile(qApp->applicationDirPath() + "./../sound/click-0" + QString::number(i) + ".wav"));
    }

    for (short i=0; i<3; i++) {
        sfxLevelup[i] = new QSoundEffect(this);
        // load files from "/exeDir/sound/levelup-0X.wav"
        sfxLevelup[i]->setSource(QUrl::fromLocalFile(qApp->applicationDirPath() + "./../sound/levelup-0" + QString::number(i) + ".wav"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (!_isGameRun)
        return;
    _achiveThread->addPoints();

    // play click sound
    quint8 sfxNumber = (float) qrand()/RAND_MAX * 2;

    if (!sfxClick[sfxNumber]->isPlaying()) {
        sfxClick[sfxNumber]->play();
    }

    onUpdateGui();
}

void MainWindow::on_pushButton_BuyAchive_clicked()
{
    if (!_isGameRun)
        return;

    if (_achiveThread->buyAchive()) {
        QGraphicsScene *scn = new QGraphicsScene( ui->graphicsView );
        scn->setSceneRect( ui->graphicsView->rect() );
        ui->graphicsView->setScene( scn );

        quint8 picNumber = _achiveThread->getAchiveLevel() % 10;
        if (picNumber > 4)
            picNumber = picNumber - 5;

        QPixmap pix( "./pics/" + QString::number(picNumber) + ".png" );
        scn->addPixmap( pix );
        ui->graphicsView->setStyleSheet("background-color: transparent;");

        // play levelup sound
        quint8 sfxNumber = (float) qrand()/RAND_MAX * 3;

        if (!sfxLevelup[sfxNumber]->isPlaying()) {
            sfxLevelup[sfxNumber]->play();
        }

        onUpdateGui();
    }    
}

void MainWindow::onUpdateGui() {
    if (!_isGameRun)
        return;
    ui->label_AddMoneyIndicator->setText('+'+QString::number(_achiveThread->getPointsInc(), 'E', 4));
    ui->label_Money->setText(QString::number(_achiveThread->getMyPoints(), 'E', 4));

    ui->label_nextLevelExpIndicator->setText( "of " + QString::number(_achiveThread->getCostOfLevel(_achiveThread->getMyLevel()+1), 'E', 4) );
    ui->label_Level->setText(QString::number(_achiveThread->getMyLevel()));

    if (_lastTime.elapsed() >= 3000) {
        _achiveThread->restartClicksCount();
        _lastTime.restart();
    }

    ui->label_curClickSlide->setText("+" + QString::number(_achiveThread->getUltimateValue()));
    ui->pushButton_BuyAchive->setText(QString::number(_achiveThread->getAchiveCost(), 'E', 2));
    ui->label_AchiveLevel->setText(QString::number(_achiveThread->getAchiveLevel()));
    ui->lcdNumber_myGameTime->display(QString::number( _achiveThread->getMyGameTime() ));
    ui->label_AddPointAchiveIndecator->setText("+" + QString::number(_achiveThread->getPointsIncAchivements(), 'E', 2));

    quint8 frameNumber = _achiveThread->getUltimateIndex()+_achiveThread->getMyLevel();
    if (frameNumber > 36)
        frameNumber = 36;
    _movie->jumpToFrame(frameNumber);
    ui->label_frameIndicator->setText(QString::number(frameNumber));
    ui->label_picture->setPixmap(_movie->currentPixmap());
}

void MainWindow::onUpdateLevel() {
    if (_achiveThread->getMyLevel() >= 20) { // game end. Выполянется после обновления GUI
        //ui->label_gameEnd->setVisible(true);
        _achiveThread->setRunnable(false);
        ui->pushButton_BuyAchive->setVisible(false);
        QMessageBox::warning(this,
                             "Warning!",
                             "Game is end! Your time is " + QString::number( _achiveThread->getMyGameTime() )
                             );
        _isGameRun = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    _achiveThread->start();
    _lastTime.start();
    _isGameRun = true;

    scn->addPixmap( *pix );

    bool isVisibile = true;
    ui->label->setVisible(isVisibile);
    ui->label_2->setVisible(isVisibile);
    ui->label_3->setVisible(isVisibile);
    ui->label_AchiveLevel->setVisible(isVisibile);
    ui->label_AddMoneyIndicator->setVisible(isVisibile);
    ui->label_AddPointAchiveIndecator->setVisible(isVisibile);
    ui->label_curClickSlide->setVisible(isVisibile);
    ui->label_gameEnd->setVisible(!isVisibile);
    ui->label_Level->setVisible(isVisibile);
    ui->label_Money->setVisible(isVisibile);
    ui->label_nextLevelExpIndicator->setVisible(isVisibile);
    ui->label_picture->setVisible(isVisibile);
    ui->pushButton->setVisible(isVisibile);
    ui->pushButton_2->setVisible(!isVisibile);
    ui->pushButton_BuyAchive->setVisible(isVisibile);
    ui->lcdNumber_myGameTime->setVisible(isVisibile);
    ui->graphicsView->setVisible(isVisibile);
}

// анимация ачивки
void MainWindow::on_pushButton_BuyAchive_pressed()
{
    ui->graphicsView->setGeometry(
                ui->graphicsView->x(),
                ui->graphicsView->y(),
                ui->graphicsView->width()+10,
                ui->graphicsView->height()+10
                );
    ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_BuyAchive_released()
{
    ui->graphicsView->setGeometry(
                ui->graphicsView->x(),
                ui->graphicsView->y(),
                ui->graphicsView->width()-10,
                ui->graphicsView->height()-10
                );
    ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}
// ---- анимация ачивки

