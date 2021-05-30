#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QtGui>
#include <QWidget>
#include <QMdiSubWindow>

#include "turwidget.h"

namespace Ui {
    class ChildWindow;
}

class mdiWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit mdiWindow(QWidget *parent = 0);
    ~mdiWindow();

private:
    TurWidget *turWidget;

};

#endif // MDIWINDOW_H
