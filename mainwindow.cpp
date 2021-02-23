#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

QGraphicsScene* MainWindow::Scene = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_graphicsView(new QGraphicsView)
    , m_toolbox(new QToolBox)
    , m_toolbar(new QToolBar)
    , m_menubar(new QMenuBar)
    //, m_scene(new QGraphicsScene)
{
    this->resize(860,640);

    QWidget *widget = new QWidget;

    MainWindow::Scene = new QGraphicsScene;
    m_graphicsView->setScene(MainWindow::Scene);
    //m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //m_menubar = new QMenuBar;//(widget);
    setToolBar();
    setToolBox();
    setMenuBar();

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(m_toolbox,10);
    hlayout->addWidget(m_graphicsView,90);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_menubar);
    layout->addWidget(m_toolbar);
    layout->addItem(hlayout);

    widget->setLayout(layout);
    setCentralWidget(widget);


    //GraphicsViewItem* item = new GraphicsViewItem(":/LogicOperators/OR.png");
    //item->setScene(m_scene);
    //m_scene->addItem(item);

    //QGraphicsItem* item = new QGraphicsEllipseItem(QRectF(100,100,100,100));
    //item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //item->setFlag(QGraphicsItem::ItemIsMovable, true );
    //m_scene->addItem(item);
    //
    //QLabel* label = new QLabel("Push");
    //m_scene->addWidget(label);
    Node *a = new Node(0,0);
    Node *b = new Node(50,0);

    Edge *e = new Edge(b, a);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete m_scene;
    delete m_graphicsView;
}



void MainWindow::setToolBar()
{
    m_toolbar->addWidget(new QPushButton("undo"));
    m_toolbar->addWidget(new QPushButton("redo"));
    m_toolbar->addWidget(new QPushButton("zoom in"));
    m_toolbar->addWidget(new QPushButton("zoom out"));
}

void MainWindow::setToolBox()
{
    m_toolbox->addItem(new QLabel("AND"), "Logic Operators");
    m_toolbox->addItem(new QLabel, "Labels");
    m_toolbox->addItem(new QLabel, "Triggers");
}

void MainWindow::setMenuBar()
{
    QMenu *file = new QMenu("&File");
    file->addAction("Open");
    file->addMenu("new");

    QMenu *Build = new QMenu("&Build");
    Build->addAction("Rebuild this file");
    Build->addAction("Rebuild All");

    m_menubar->addMenu(file);
    m_menubar->addMenu(Build);
}
