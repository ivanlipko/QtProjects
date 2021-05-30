// todo
//  - автоИнкримент: дать молока, убрать лоток (отрицательный), дать бусы, дать мячик


#ifndef ACHIVEMENTTIMER_H
#define ACHIVEMENTTIMER_H

#include <QThread>
#include "ultimate.h"

const quint8 levelCount = 30;

class AchivementTimer : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE ;
    bool _isRunable;

    quint8 _myLevel;
    quint64 _myPoints;
    quint8 _myAchiveLevel;

    quint32 _costOfLevel[levelCount];
    quint32 _costOfAchivements[levelCount];
    quint8 _incOfUltimate[levelCount][levelCount];

    quint16 _pointsIncAchivements[levelCount][levelCount];
    quint16 _pointsInc[levelCount][levelCount];
    quint8 _clicksCount;

    quint64 _myGameTime;

    Ultimate *_ultimate;

public:
    AchivementTimer();

    void addPoints();
    quint16 getPointsInc();
    quint8 getMyLevel();
    quint32 getMyPoints();
    quint32 getCostOfLevel(quint8 i);
    quint8 getClicksCount();
    void restartClicksCount();
    quint8 getUltimateValue();
    quint32 getUltimateIndex();
    bool buyAchive();
    quint32 getAchiveCost();
    quint8 getAchiveLevel();
    quint64 getMyGameTime();
    quint16 getPointsIncAchivements();

    void setRunnable(bool isRunable);

signals:
    void updateGUI();
    void updateLevel();
};

#endif // ACHIVEMENTTIMER_H
