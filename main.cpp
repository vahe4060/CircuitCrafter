#include "mainwindow.h"

//#include <QApplication>
//#include <QtGui>
//#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow::instance()->show();
    return app.exec();
}
