#include "turwidget.h"
#include "ui_turwidget.h"

#define TABLE_USER_RATING 1

#define TABLE_RATING_TOTAL_POINTS 0
#define TABLE_RATING_TOTAL_K 1
#define TABLE_RATING_POSITION 2
#define TABLE_RATING_NEW_RATING 3
#define TABLE_RATING_MASTER 4

#define TABLE_DATA_ENEMYS_COEF 0

#define FIGHTS_COUNT 8


float calcNewRating(
        float oldRating,
        float sumPoints,
        unsigned short partiesCount,
        unsigned short enemysCount,
        float enemysCoeff ) {
    return 1.0 * (20*oldRating+enemysCoeff+5000*(2*sumPoints-partiesCount)/17)/(20+enemysCount);
}

TurWidget::TurWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TurWidget)
{
    ui->setupUi(this);
}

TurWidget::~TurWidget()
{
    delete ui;
}

void TurWidget::on_tableWidgetFights_cellPressed(int row, int column)
{
//    ui->tableWidgetFights->setItem(row, column, new QTableWidgetItem(QString::number(row)+ " " + QString::number(column)));
}

void TurWidget::on_tableWidgetFights_cellChanged(int row, int column)
{
    // количество очков набранных игроком
    float sumPoints = 0.0;
    unsigned short tableColumnCount = ui->tableWidgetFights->columnCount();
    for (int i=0; i < tableColumnCount; i++)
        if ( ui->tableWidgetFights->item(row,i) ) //must be 0,1 or 2
            sumPoints += ui->tableWidgetFights->item(row,i)->text().toFloat() * 0.5;
    ui->tableWidgetRating->setItem(row, TABLE_RATING_TOTAL_POINTS, new QTableWidgetItem(QString::number( sumPoints )));
}

void TurWidget::on_tableWidgetUsers_cellChanged(int row, int column)
{

    unsigned short tableRowCount = ui->tableWidgetFights->rowCount();
    for (int j=0; j < tableRowCount; j++) {
        // пересчёт всех коеффициентов соперников
        unsigned int enemesSumCoefficient = 0;
        for (int i=0; i < tableRowCount; i++)   //сумма коеф. для соперника
            if (ui->tableWidgetUsers->item(i,1))
                if (i != j)
                    enemesSumCoefficient += ui->tableWidgetUsers->item(i,1)->text().toInt();
        ui->tableWidgetData->setItem(j, TABLE_DATA_ENEMYS_COEF, new QTableWidgetItem(QString::number( enemesSumCoefficient )));

        // новый рейтинг игрока
        float oldRating = 0;
        float sumPoints = 0;
        unsigned short partiesCount = 0;
        unsigned short enemysCount = 0;
        float enemesCoefficient = 0;

        if (ui->tableWidgetUsers->item(j,TABLE_USER_RATING))
            oldRating = ui->tableWidgetUsers->item(j,TABLE_USER_RATING)->text().toFloat();
        if (ui->tableWidgetRating->item(j,TABLE_RATING_TOTAL_POINTS))
            sumPoints = ui->tableWidgetRating->item(j,TABLE_RATING_TOTAL_POINTS)->text().toFloat();
        if (ui->tableWidgetFights->columnCount())
            partiesCount = ui->tableWidgetFights->columnCount() - 2; // -2, т.к. 2 игры на каждую встречу
        if (ui->tableWidgetUsers->rowCount())
            enemysCount = ui->tableWidgetUsers->rowCount() - 1; // -1, чтобы не считать себя
        if (ui->tableWidgetData->item(j,TABLE_DATA_ENEMYS_COEF))
            enemesCoefficient = ui->tableWidgetData->item(j,TABLE_DATA_ENEMYS_COEF)->text().toFloat();

        float newRating = calcNewRating(oldRating,
                                        sumPoints,
                                        partiesCount,
                                        enemysCount,
                                        enemesCoefficient
                                    );
        ui->tableWidgetRating->setItem(j, TABLE_RATING_NEW_RATING, new QTableWidgetItem(QString::number(newRating)));

        QString masterLevel = "";
        if (newRating > 800) {
            masterLevel = "МС";
        } else {
            if (newRating >= 700){
                masterLevel = "КМС";
            } else {
                if (newRating >= 600){
                    masterLevel = "1 кандидатский балл";
                }else{
                    if (newRating >= 500){
                        masterLevel = "1 разряд";
                    } else {
                        if (newRating >= 400){
                            masterLevel = "2 разряд";
                        } else {
                            if (newRating >= 300){
                                masterLevel = "3 разряд";
                            };
                        }
                    }
                }
            }
        }
        ui->tableWidgetRating->setItem(j, TABLE_RATING_MASTER, new QTableWidgetItem(masterLevel));
    }
}

// количество партий, сыграных игроком (в течении турнира по идее остаётся одинаковым)
//  может стоит это сделать при настройке турнира
//    unsigned short partiesCount = ui->tableWidgetFights->columnCount();
//    ui->tableWidgetRating->setItem(row, TABLE_RATING_, new QTableWidgetItem(QString::number( partiesCount )));

// количество соперников игрока (в течении турнира по идее остаётся одинаковым)
//  может стоит это сделать при настройке турнира
//    unsigned short EnemesCount = ui->tableWidgetUsers->rowCount();
//    ui->tableWidgetRating->setItem(row, TABLE_RATING_, new QTableWidgetItem(QString::number( EnemesCount )));

void TurWidget::on_pushButtonAddUser_clicked()
{
    int lastRow = ui->tableWidgetUsers->rowCount();
    ui->tableWidgetUsers->insertRow( lastRow );
    ui->tableWidgetFights->insertRow( lastRow );
        //cycle of column adding
    ui->tableWidgetFights->insertColumn( 2*lastRow  );
    ui->tableWidgetFights->insertColumn( 2*lastRow+1  );
    ui->tableWidgetFights->setItem(lastRow, 2*lastRow, new QTableWidgetItem(QString("=")));
    ui->tableWidgetFights->setItem(lastRow, 2*lastRow+1, new QTableWidgetItem(QString("=")));
    ui->tableWidgetRating->insertRow( lastRow );
    ui->tableWidgetData->insertRow( lastRow );
}

void TurWidget::on_pushButtonDeleteUser_clicked()
{
    int currentRow = ui->tableWidgetUsers->currentRow();
    ui->tableWidgetUsers->removeRow(currentRow);
    ui->tableWidgetFights->removeRow(currentRow);
    ui->tableWidgetFights->removeColumn( 2*currentRow  ); // remove column of 1st enemy
    ui->tableWidgetFights->removeColumn( 2*currentRow  ); // remove column of 2nd enemy

    ui->tableWidgetRating->removeRow(currentRow);
    ui->tableWidgetData->removeRow(currentRow);
}
