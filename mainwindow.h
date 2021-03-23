#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
//#include "output_node.h"
//#include "input_node.h"
//#include "edge.h"
//#include "graphicsceneitem.h"
#include "labels.h"
#include "operators.h"
#include "graphicslineitem.h"
#include "graphicsscene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void addToScene(QString itemtype);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QGraphicsView* View;
    static GraphicsScene* Scene;
    static QGraphicsItem* Center;


protected:
    //Ui::MainWindow *ui;
    //QGraphicsView* m_graphicsView = nullptr;
    QToolBar* m_toolbar_operators = nullptr;
    QToolBar* m_toolbar_tools = nullptr;

    void setToolBar();
    void setMenuBar();
};

#endif // MAINWINDOW_H
