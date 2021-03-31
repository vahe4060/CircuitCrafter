#include "mainwindow.h"

//#include <QApplication>
//#include <QtGui>
//#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::instance()->show();
    return a.exec();
}
