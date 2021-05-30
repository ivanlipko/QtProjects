#include "ultimate.h"

#include "QDebug"

Ultimate::Ultimate()
{
    _isRunable = true;
    _timePause = 100;
    _destiny = 0;
    _curValue = 0;
}

void Ultimate::run() Q_DECL_OVERRIDE {
    qint32 incc = 0;
    while(_isRunable) {
        incc = 0;
        if (_destiny > _curValue)
            incc = 1;
        if (_destiny < _curValue)
            incc = -1;

        if (incc > 65530){
            qDebug() << "! incc=" << incc;
            incc = 65530;
        }
        if (incc < -65530){
            qDebug() << "! incc=" << incc;
            incc = -65530;
        }

        _curValue = _curValue + incc;

        msleep(_timePause);
    }
}

quint32 Ultimate::getCurValue() {
    return _curValue;
}

void Ultimate::setDestiny(quint32 destiny) {
    _destiny = destiny;
}
