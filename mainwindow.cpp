#include "mainwindow.h"

QGraphicsView* MainWindow::View = nullptr;
GraphicsScene* MainWindow::Scene = nullptr;
QGraphicsItem* MainWindow::Center = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(860,640);
    QWidget *widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    if(!MainWindow::Scene)
    {
        MainWindow::Scene = new GraphicsScene;
        MainWindow::Scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    }
    if(!MainWindow::Center)
    {
        MainWindow::Center = new QGraphicsEllipseItem(0,0,1,1, nullptr);
        MainWindow::Scene->addItem(MainWindow::Center);
    }
    if(!MainWindow::View)
        MainWindow::View = new QGraphicsView(MainWindow::Scene);


    setToolBar();
    setMenuBar();



    //layout->addWidget(m_toolbox,5);
    //layout->addWidget(m_graphicsView,95);
    layout->addWidget(MainWindow::View);
    widget->setLayout(layout);
    setCentralWidget(widget);



    //Label* l = new Label(SceneItem::INPUT,  140,80,  MainWindow::Center);
    //Label* m = new Label(SceneItem::INPUT,  -40,80,  MainWindow::Center);
    //Label* n = new Label(SceneItem::INPUT,  40,80,   MainWindow::Center);
    //Label* o = new Label(SceneItem::OUTPUT, 190,100, MainWindow::Center);
    //Label* p = new Label(SceneItem::OUTPUT, 190,100, MainWindow::Center);
    //
    //
    //Operator* a = new Operator(SceneItem::AND,  50,100, MainWindow::Center);
    //Operator* b = new Operator(SceneItem::XNOR, 50,100, MainWindow::Center);
    //Operator* c = new Operator(SceneItem::NOR,  50,100, MainWindow::Center);
    //Operator* d = new Operator(SceneItem::NOT,  50,100, MainWindow::Center);
    //Operator* e = new Operator(SceneItem::XOR,  50,100, MainWindow::Center);
    //Operator* f = new Operator(SceneItem::NAND, 50,100, MainWindow::Center);
    //Operator* g = new Operator(SceneItem::OR,   50,100, MainWindow::Center);

}


MainWindow::~MainWindow()
{
    delete MainWindow::Center;
    delete MainWindow::Scene;
    delete MainWindow::View;
}


void MainWindow::addToScene(QString itemname)
{
    SceneItem::TYPE t;
    if(itemname == "NOT")
        t =SceneItem::TYPE::NOT;
    else if(itemname == "AND")
        t = SceneItem::TYPE::AND;
    else if(itemname == "OR")
        t = SceneItem::TYPE::OR;
    else if(itemname == "XOR")
        t = SceneItem::TYPE::XOR;
    else if(itemname == "NAND")
        t = SceneItem::TYPE::NAND;
    else if(itemname == "NOR")
        t = SceneItem::TYPE::NOR;
    else if(itemname == "XNOR")
        t = SceneItem::TYPE::XNOR;
    else if(itemname == "IN")
        t = SceneItem::TYPE::INPUT;
    else if(itemname == "OUT")
        t = SceneItem::TYPE::OUTPUT;
    else if(itemname == "NOT")
        t = SceneItem::TYPE::NOT;
    else
        return;

    MainWindow::Scene->setCurrent(t);

    if(t == SceneItem::INPUT || t == SceneItem::OUTPUT)
        MainWindow::View->setCursor(QCursor(QPixmap(":/Labels/images/" + SceneItem::types[t] + ".png"), 0,0));
    else
        MainWindow::View->setCursor(QCursor(QPixmap(":/Operators/images/" + SceneItem::types[t] + ".png"), 0,0));
}


void MainWindow::setToolBar()
{
    m_toolbar_operators = addToolBar(tr("Operators"));
    m_toolbar_tools = addToolBar(tr("Tools"));

    QDir dir(":/Tools/images/");
    for(uint i=0; i< dir.count(); i++)
    {
        QAction* action = m_toolbar_tools->addAction(QIcon(":/Tools/images/" +dir[i]), dir[i].split(".")[0]);
        m_toolbar_tools->addSeparator();
    }


    QSignalMapper* signalMapper = new QSignalMapper(this);

    dir.setPath(":/Operators/images/");
    for(uint i=0; i< dir.count(); i++)
    {
        QString itemname = dir[i].split(".")[0];
        QAction* action = m_toolbar_operators->addAction(QIcon(":/Operators/images/" +dir[i]), itemname);

        signalMapper->setMapping(action, itemname);

        connect(action, SIGNAL(triggered()),
                signalMapper, SLOT (map()));
    }

    m_toolbar_operators->addSeparator();


    dir.setPath(":/Labels/images/");
    for(uint i=0; i< dir.count(); i++)
    {
        QString itemname = dir[i].split(".")[0];
        QAction* action = m_toolbar_operators->addAction(QIcon(":/Labels/images/" +dir[i]), itemname);

        signalMapper->setMapping(action, itemname);

        connect(action, SIGNAL(triggered()),
                signalMapper, SLOT (map()));
    }


    connect(signalMapper, SIGNAL(mapped(QString)),
            this, SLOT(addToScene(QString)));
}



void MainWindow::setMenuBar()
{

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction("Open");
    fileMenu->addAction("New");

    QMenu* itemMenu = menuBar()->addMenu(tr("&Item"));
    itemMenu->addAction("Rebuild this file");
    itemMenu->addSeparator();
    itemMenu->addAction("Rebuild all");

    QMenu* aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction("About");

    //QMenu *file = new QMenu("&File");
    //file->addAction("Open");
    //file->addMenu("new");
    //
    //QMenu *Build = new QMenu("&Build");
    //Build->addAction("Rebuild this file");
    //Build->addAction("Rebuild All");
    //
    //m_menubar->addMenu(file);
    //m_menubar->addMenu(Build);
}
