//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

#include <QObject>
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QtGui/QIcon>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>

class MyReceiver : public QObject
{
    Q_OBJECT

public:
    MyReceiver() {}
public slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);
};

//MyReceiver::MyReceiver(){

//}


class Counter : public QObject
{
  Q_OBJECT

public:
  Counter() { m_value = 0; }

  int value() const { return m_value; }

public slots:
  void setValue(int value);

signals:
  void valueChanged(int newValue);

private:
  int m_value;
};


void MyReceiver::onActivated(QSystemTrayIcon::ActivationReason reason){
    exit(0);
    return;
}

//void onActivated(QSystemTrayIcon::ActivationReason reason){
//    exit(0);
//    return;
//}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QPixmap oPixmap(32,32);
    //QMenu* menu1 = new QMenu(); // want to get a context menu from system tray
    oPixmap.load ("systemTrayIcon.png");
    QIcon oIcon( oPixmap );

    MyReceiver receiver;
    Counter counter;

//    QAction *quitAction;
//    quitAction = new QAction("&Quit");
//    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);



//    QMenu *trayIconMenu;
//    trayIconMenu = new QMenu();
//    trayIconMenu->addSeparator();
//    trayIconMenu->addAction(quitAction);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(oIcon);
    qDebug() << trayIcon->isSystemTrayAvailable();
//    trayIcon->setContextMenu( trayIconMenu);
    trayIcon->setVisible(true);
    trayIcon->showMessage("Test Message", "Text", QSystemTrayIcon::Information, 1000);

//    connect(trayIcon, &QSystemTrayIcon::activated, &onActivated);
    QObject::connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            &receiver, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));


    return app.exec();
}
