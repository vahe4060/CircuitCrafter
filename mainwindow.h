#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView* m_graphicsView = nullptr;
    QGraphicsScene* m_scene = nullptr;
    QLayout* m_layout = nullptr;
    QToolBox* m_toolbox = nullptr;

};
#endif // MAINWINDOW_H
