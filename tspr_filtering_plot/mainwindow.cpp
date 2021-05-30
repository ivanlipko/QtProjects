#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройки вида графиков

    // сделает график интерактивным.
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // initialize axis range (and scroll bar positions via signals we just connected):
    ui->plot->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plot->yAxis->setRange(0, 10, Qt::AlignCenter);

    ui->plot->addGraph();
    ui->plot->addGraph();
    ui->plot->addGraph();

    QCPScatterStyle scClear;
    scClear.setShape(QCPScatterStyle::ssCircle);
    scClear.setPen(QPen(Qt::blue));
    scClear.setBrush(Qt::white);
    scClear.setSize(5);
    ui->plot->graph(0)->setScatterStyle(scClear);
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    ui->plot->graph(0)->setName("Исходный");

    QCPScatterStyle scNoise;
    scNoise.setShape(QCPScatterStyle::ssCircle);
    scNoise.setPen(QPen(Qt::red));
    scNoise.setBrush(Qt::white);
    scNoise.setSize(5);
    ui->plot->graph(1)->setScatterStyle(scNoise);
    ui->plot->graph(1)->setPen(QPen(Qt::red));
    ui->plot->graph(1)->setName("Зашумлённый");

    QCPScatterStyle scFilt;
    scFilt.setShape(QCPScatterStyle::ssCircle);
    scFilt.setPen(QPen(Qt::green));
    scFilt.setBrush(Qt::green);
    scFilt.setSize(5);
    ui->plot->graph(2)->setScatterStyle(scFilt);
    ui->plot->graph(2)->setPen(QPen(Qt::green));
    ui->plot->graph(2)->setName("Фильтрованный");

    ui->plot->xAxis->setAutoTickStep(false);
    ui->plot->xAxis->setTickStep(1);
    ui->plot->xAxis->setLabel("Момент времени");
    ui->plot->yAxis->setLabel("Значение");

    ui->plot->plotLayout()->insertRow(0);
    ui->plot->plotLayout()->addElement(0, 0, new QCPPlotTitle( ui->plot, "Входные данные"));

    ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    ui->plot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);

//    ui->plot->replot();

    updateCharts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add2plot(int plotnum, std::array <int, LENGTH> time, std::array <int, LENGTH> data){
    QVector<double> tIndex;
    tIndex.reserve(time.size()); // warning: size_t->int cast
    std::copy(time.begin(), time.end(), std::back_inserter(tIndex));

    QVector<double> dIndex;
    dIndex.reserve(data.size()); // warning: size_t->int cast
    std::copy(data.begin(), data.end(), std::back_inserter(dIndex));
    ui->plot->graph(plotnum)->setData(tIndex, dIndex);
}

void MainWindow::updateCharts() {
    std::array <int, LENGTH> time;
    std::array <int, LENGTH> clearSignal;
    std::array <int, LENGTH> noisedSignal;
    std::array <int, LENGTH> filtSignal;

    for (unsigned int i = 0; i < time.size(); i++) {
        time[i] = i;
    }

    generate(clearSignal);
    addNoise(clearSignal, noisedSignal);
    filtrate(noisedSignal, filtSignal);

    add2plot(0, time, clearSignal);
    add2plot(1, time, noisedSignal);
    add2plot(2, time, filtSignal);

    double minY = * std::min_element(noisedSignal.begin(), noisedSignal.end());
    double maxY = * std::max_element(noisedSignal.begin(), noisedSignal.end());

    ui->plot->xAxis->setRange(0, LENGTH+1);
    ui->plot->yAxis->setRange(minY-1, maxY+1);
    ui->plot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    updateCharts();
}

/* Это реакция на сдвиг слайдера: значение слайдера присваиваем в коэффициент
К экспоненциального фильтра */
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    filtavg_K = (float) value / 100;

}
