#include "mainwindow.h"


QGraphicsScene* MainWindow::Scene = nullptr;
QGraphicsItem* MainWindow::Center = new QGraphicsEllipseItem(0,0,1,1, nullptr);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_graphicsView(new QGraphicsView)
{
    this->resize(860,640);
    QWidget *widget = new QWidget;

    if(!MainWindow::Scene)
        MainWindow::Scene = new QGraphicsScene;
    MainWindow::Scene->addItem(MainWindow::Center);


    m_graphicsView->setScene(MainWindow::Scene);

    setToolBar();
    setToolBox();
    setMenuBar();


    QVBoxLayout* layout = new QVBoxLayout;
    //layout->addWidget(m_toolbox,5);
    //layout->addWidget(m_graphicsView,95);
    layout->addWidget(m_graphicsView);

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
    delete m_graphicsView;
}

void MainWindow::addToScene(QString itemname)
{

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

void MainWindow::setToolBox()
{

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
