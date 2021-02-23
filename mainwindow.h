#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "node.h"
#include "edge.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QGraphicsScene* Scene;
private:
    Ui::MainWindow *ui;
    QGraphicsView* m_graphicsView = nullptr;
    QToolBox* m_toolbox = nullptr;
    QToolBar* m_toolbar = nullptr;
    QMenuBar* m_menubar = nullptr;
    //QGraphicsScene* m_scene = nullptr;

protected:
    void setToolBar();
    void setToolBox();
    void setMenuBar();
};

#endif // MAINWINDOW_H
