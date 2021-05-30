#include "achivementtimer.h"

#include "QtMath"
#include "QDebug"


AchivementTimer::AchivementTimer()
{
    _isRunable = true;

    _myLevel = 0;
    _myAchiveLevel = 0;
    _myPoints = 0;

    _clicksCount = 0;
    _myGameTime = 0;

    for (short i=1; i<levelCount; i++) {
        _costOfLevel[i-1] = qPow(i,3)*15;
        _costOfAchivements[i-1] = qPow(i,3)*10;
    }

    for (short i=1; i<levelCount; i++) {
        for (short j=1; j<levelCount; j++) {
            _pointsInc[i-1][j-1] = i*j*2;
            _pointsIncAchivements[i-1][j-1] = _pointsInc[i-1][j-1]/50;
            _incOfUltimate[i-1][j-1] = _pointsInc[i-1][j-1]/25;
       }
    }

    _ultimate = new Ultimate();
    connect(_ultimate, &Ultimate::finished, _ultimate, &QObject::deleteLater);
    _ultimate->start();
}

void AchivementTimer::run() Q_DECL_OVERRIDE {
    _clicksCount = 36;
    while(_isRunable) {
        _ultimate->setDestiny(_clicksCount);

        _myPoints= _myPoints + getUltimateValue();
        _myPoints= _myPoints + _pointsIncAchivements[_myLevel][_myAchiveLevel];

        if (_myPoints >= _costOfLevel[_myLevel+1]) {
            _myLevel = _myLevel + 1;
            emit updateLevel();
        }

        _myGameTime = _myGameTime + 1;

        emit updateGUI();
        msleep(10);
    }
}

void AchivementTimer::addPoints() {
    _myPoints = _myPoints + _pointsInc[_myLevel][_myAchiveLevel];
    _clicksCount = _clicksCount + 1;
}

quint16 AchivementTimer::getPointsInc(){
    return _pointsInc[_myLevel][_myAchiveLevel];
}

quint32 AchivementTimer::getMyPoints(){
    return _myPoints;
}

quint32 AchivementTimer::getCostOfLevel(quint8 i) {
    return _costOfLevel[i];
}

quint8 AchivementTimer::getMyLevel(){
    return _myLevel;
}

quint8 AchivementTimer::getClicksCount() {
    return _clicksCount;
}

void AchivementTimer::restartClicksCount() {
    _clicksCount = 0;
}

quint8 AchivementTimer::getUltimateValue(){
    if (_clicksCount > levelCount)
        _clicksCount = levelCount;
    return _incOfUltimate[_myLevel][_clicksCount];
}

quint32 AchivementTimer::getUltimateIndex(){
    return _ultimate->getCurValue();
}

bool AchivementTimer::buyAchive(){
    if (_myPoints >= _costOfAchivements[_myAchiveLevel] && _myAchiveLevel < levelCount - 1) {
        _myPoints = _myPoints - _costOfAchivements[_myAchiveLevel];
        _myAchiveLevel = _myAchiveLevel + 1;
        return true;
    }
    return false;
}

quint32 AchivementTimer::getAchiveCost(){
    return _costOfAchivements[_myAchiveLevel];
}

quint8 AchivementTimer::getAchiveLevel() {
    return _myAchiveLevel;
}

quint64 AchivementTimer::getMyGameTime() {
    return _myGameTime;
}

quint16 AchivementTimer::getPointsIncAchivements(){
    return _pointsIncAchivements[_myLevel][_myAchiveLevel];
}

void AchivementTimer::setRunnable(bool isRunable) {
    _isRunable = isRunable;
}
