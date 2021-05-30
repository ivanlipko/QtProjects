#ifndef ULTIMATE_H
#define ULTIMATE_H
#include <QThread>

class Ultimate : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE ;

    bool _isRunable;

    quint16 _timePause; //unsigned 2 bytes
    quint32 _destiny;
    quint32 _curValue;


public:
    Ultimate();

    quint32 getCurValue();
    void setDestiny(quint32 destiny);
};

#endif // ULTIMATE_H
