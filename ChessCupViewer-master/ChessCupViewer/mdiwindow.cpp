#include "mdiwindow.h"
#include "turwidget.h"

#include <QMdiSubWindow>


mdiWindow::mdiWindow(QWidget *parent) :
    QMdiSubWindow(parent)
{
    turWidget = new TurWidget(this);
    this->setWidget(turWidget);
}

mdiWindow::~mdiWindow()
{
    turWidget->~TurWidget();
}
