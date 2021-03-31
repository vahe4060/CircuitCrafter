#include "mainwindow.h"
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QShortcut>
#include <QMessageBox>

MainWindow* MainWindow::m_instance = nullptr;

bool MainWindow::autoSave = false;
Qt::GlobalColor MainWindow::wireColor = Qt::black;
bool MainWindow::showAxes = false;

Qt::GlobalColor MainWindow::WireColor()
{
    return wireColor;
}

MainWindow* MainWindow::instance()
{
    if(!m_instance)
        m_instance = new MainWindow;
    return m_instance;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(860,640);
    setWindowTitle("");
    QWidget *widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    m_Center = new QGraphicsEllipseItem(0,0,1,1, nullptr);
    m_Scene = new GraphicsScene;
    m_Scene->setSceneRect(QRectF(-2500, -2500, 5000, 5000));
    m_Scene->addItem(m_Center);
    m_View = new QGraphicsView(m_Scene);

    layout->addWidget(m_View);
    widget->setLayout(layout);
    setCentralWidget(widget);

    loadSettings();
    setToolBar();
    setMenuBar();
    loadAxes();
    setNotUpdatedFlag();
}


MainWindow::~MainWindow()
{
    delete m_Center;
    delete m_Scene;
    delete m_View;
    delete m_toolbar_operators;
    delete m_toolbar_tools;
    delete m_instance;
}

void MainWindow::newDocument()
{
    if(updated)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save current file?", "Save current file?",
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if (reply == QMessageBox::Yes)
        {
           save();
        }
        else if(reply == QMessageBox::Cancel)
        {
           return;
        }
    }

    for(QGraphicsItem* it: m_Center->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            delete it;
    }
    for(QGraphicsItem* it: m_Center->childItems())
    {
        delete it;
    }

    currentPath = "";
    setNotUpdatedFlag();
}


void MainWindow::loadSettings()
{
    QFile file(":/params/settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    QJsonObject settingsJson = JsonDocument.object();
    autoSave = settingsJson["Autosave"].toBool();
    wireColor = Qt::GlobalColor(settingsJson["Wire"].toInt());
    showAxes = settingsJson["Axes"].toBool();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QJsonObject settingsJson;
    settingsJson["Wire"] = wireColor;
    settingsJson["Autosave"] = autoSave;
    settingsJson["Axes"] = showAxes;
    QJsonDocument JsonDocument;
    JsonDocument.setObject(settingsJson);

    QFile file("C:/Users/vahe2/Documents/Diploma/settings.json");
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();

    if(autoSave)
        if(updated)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Exit without saving?", "Save changes before exit?",
                                          QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

            if (reply == QMessageBox::Yes)
            {
               save();
            }
            else if(reply == QMessageBox::Cancel)
            {
               event->ignore();
            }
        }
}

void MainWindow::setUpdatedFlag()
{
    updated = true;
    setWindowTitle("(UNSAVED)   " + currentPath);
}

void MainWindow::setNotUpdatedFlag()
{
    updated = false;
    setWindowTitle(currentPath);
}

void MainWindow::resetSettings()
{
    zoom(0);
    showAxes = true;
    showAxesAction->setChecked(true);
    autoSave = false;
    autoSaveAction->setChecked(false);

    wireColor = Qt::black;
    QPen pen(QBrush(wireColor), 2);
    for(QGraphicsItem* it:m_Center->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            static_cast<Edge*>(it)->highlight(pen);
    }
}

void MainWindow::setDrawingObject(QString itemname)
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

    m_Scene->setCurrent(t);

    if(t == SceneItem::INPUT || t == SceneItem::OUTPUT)
        m_View->setCursor(QCursor(QPixmap(":/Labels/images/" + SceneItem::types[t] + ".png"), 0,0));
    else
        m_View->setCursor(QCursor(QPixmap(":/Operators/images/" + SceneItem::types[t] + ".png"), 0,0));
}

void MainWindow::stopDrawingObject()
{
    m_Scene->setDrawing(false);
    m_Scene->setErasing(false);
    m_View->setCursor(QCursor());
}

void MainWindow::zoom(int zoomin)
{
    if(zoomin > 0)
        m_View->scale(1.1, 1.1);
    else if(zoomin < 0)
        m_View->scale(0.909, 0.909);
    else
        m_View->resetTransform();
}

void MainWindow::eraser()
{
    m_View->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    m_Scene->setErasing(true);
    m_Scene->setDrawing(false);
}

void MainWindow::eraseAll()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Eraser", "Are you sure you want to erase everything?",
                                    QMessageBox::Yes|QMessageBox::No);

      if (reply == QMessageBox::Yes)
      {
          // firstly delete Edges, then the operators/labels
          for(QGraphicsItem* it: m_Center->childItems())
          {
              if(it->type() == Edge::TYPE::EDGE)
                  delete it;
          }
          for(QGraphicsItem* it: m_Center->childItems())
          {
              delete it;
          }

      }
}

void MainWindow::save()
{
    if(currentPath == "")
    {
        QString fileName = QFileDialog::getSaveFileName();
        if(fileName == "")
            return;
        currentPath = fileName;
    }

    QList<QGraphicsItem*> items = m_Center->childItems();
    QJsonArray levelObjects, levelEdges;

    for(QGraphicsItem* i: items)
        if(i->type() == Edge::TYPE::EDGE)
        {
            Edge *it = static_cast<Edge*>(i);
            QJsonObject RootObject;

            QJsonObject left;
            left["x"] = it->left()->x() + it->left()->r();
            left["y"] = it->left()->y() + it->left()->r();

            QJsonObject right;
            right["x"] = it->right()->x() + it->right()->r();
            right["y"] = it->right()->y() + it->right()->r();

            RootObject["left"] = left;
            RootObject["right"] = right;

            levelEdges.append(RootObject);
        }
        else
        {
            SceneItem*it = static_cast<SceneItem*>(i);

            QJsonObject RootObject;
            RootObject["id"] = it->id();
            RootObject["type"] = it->type();

            QJsonObject pos;
            pos["x"] = it->pos().x();
            pos["y"] = it->pos().y();
            RootObject["pos"] = pos;

            levelObjects.append(RootObject);
        }

    QJsonObject finalObject;
    finalObject["operators"] = levelObjects;
    finalObject["edges"] = levelEdges;

    QJsonDocument JsonDocument;
    JsonDocument.setObject(finalObject);

    QFile file(currentPath);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();

    setNotUpdatedFlag();
}

void MainWindow::load()
{
    if(updated)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save current file?", "Save current file?",
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if (reply == QMessageBox::Yes)
        {
           save();
        }
        else if(reply == QMessageBox::Cancel)
        {
           return;
        }
    }
    for(QGraphicsItem* it: m_Center->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            delete it;
    }
    for(QGraphicsItem* it: m_Center->childItems())
    {
        delete it;
    }


    QString fileName = QFileDialog::getOpenFileName();
    if(fileName == "")
        return;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    QJsonObject object = JsonDocument.object();

    QJsonArray operators = object["operators"].toArray();
    QJsonArray edges = object["edges"].toArray();

    for(QJsonValueRef i: operators)
    {
        QJsonObject it = i.toObject();

        SceneItem::TYPE t = static_cast<SceneItem::TYPE>(it["type"].toInt());
        int id = it["id"].toInt();
        int x = it["pos"].toObject()["x"].toDouble();
        int y = it["pos"].toObject()["y"].toDouble();

        if(t == SceneItem::TYPE::INPUT || t == SceneItem::TYPE::OUTPUT)
        {
            new Label(id, t, x, y, m_Center);
        }
        else
        {
            new Operator(id, t, x, y, m_Center);
        }
        m_objectCount = (m_objectCount>id)?m_objectCount:id;
        m_objectCount++;
    }
    for(QJsonValueRef i: edges)
    {
        QJsonObject it = i.toObject();
        int x1 = it["left"].toObject()["x"].toDouble();
        int y1 = it["left"].toObject()["y"].toDouble();
        int x2 = it["right"].toObject()["x"].toDouble();
        int y2 = it["right"].toObject()["y"].toDouble();

        Node* left =  static_cast<Node*>(m_Scene->itemAt(QPointF(x1,y1), QTransform()));
        Node* right = static_cast<Node*>(m_Scene->itemAt(QPointF(x2,y2), QTransform()));

        left->addEdge(right);
    }

    currentPath = fileName;
    setNotUpdatedFlag();
}

void MainWindow::loadAxes()
{
    m_Scene->loadAxes(showAxes);
}

void MainWindow::setAutoSave()
{
    autoSave = !autoSave;
}

void MainWindow::setShowAxes()
{
    showAxes = !showAxes;
    loadAxes();
}

void MainWindow::about()
{
    QMessageBox::question(this, "about", "\tQt version:           5.15.0"
                                         "\n"
                                         "\n"
                                         "\tQt Creator version:   4.12.4",
                          QMessageBox::Ok);
}


void MainWindow::setToolBar()
{
    m_toolbar_operators = addToolBar(tr("Operators"));
    m_toolbar_tools = addToolBar(tr("Tools"));

    QAction* actionMouse = m_toolbar_tools->addAction(QIcon(":/Tools/images/Mouse.png"), "Mouse");
    connect(actionMouse, SIGNAL(triggered()),
            this, SLOT(stopDrawingObject()));

    m_toolbar_tools->addSeparator();
    QSignalMapper* signalMapper = new QSignalMapper(this);

    QAction* actionZoomIn = m_toolbar_tools->addAction(QIcon(":/Tools/images/ZoomIn.png"), "Zoom In");
    signalMapper->setMapping(actionZoomIn, 1);
    connect(actionZoomIn, SIGNAL(triggered()),
            signalMapper, SLOT (map()));

    QAction* actionZoomOut = m_toolbar_tools->addAction(QIcon(":/Tools/images/ZoomOut.png"), "Zoom Out");
    signalMapper->setMapping(actionZoomOut, -1);
    connect(actionZoomOut, SIGNAL(triggered()),
            signalMapper, SLOT (map()));

    QAction* actionZoomReset = m_toolbar_tools->addAction(QIcon(":/Tools/images/ZoomReset.png"), "Reset Zoom");
    signalMapper->setMapping(actionZoomReset, 0);
    connect(actionZoomReset, SIGNAL(triggered()),
            signalMapper, SLOT (map()));

    connect(signalMapper, SIGNAL(mapped(int)),
            this, SLOT(zoom(int)));

    m_toolbar_tools->addSeparator();

    QAction* actionEraser = m_toolbar_tools->addAction(QIcon(":/Tools/images/Eraser.png"), "Eraser");
    connect(actionEraser, SIGNAL(triggered()),
            this, SLOT (eraser()));

    QAction* actionEraseAll = m_toolbar_tools->addAction(QIcon(":/Tools/images/EraseAll.png"), "Erase Everything");
    connect(actionEraseAll, SIGNAL(triggered()),
            this, SLOT (eraseAll()));


    signalMapper = new QSignalMapper(this);

    QDir dir(":/Operators/images/");
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
            this, SLOT(setDrawingObject(QString)));
}


void MainWindow::setMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QAction* newAction = fileMenu->addAction("New");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newDocument()));

    QAction* openAction = fileMenu->addAction("Open");
    connect(openAction, SIGNAL(triggered()), this, SLOT(load()));

    fileMenu->addSeparator();

    QAction* saveAction = fileMenu->addAction("Save");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    QMenu* itemMenu = menuBar()->addMenu(tr("&Project"));
    itemMenu->addAction("Build");
    itemMenu->addAction("Rebuild");

    QMenu* settingsMenu = menuBar()->addMenu(tr("&Settings"));

    QMenu* prefereneMenu = settingsMenu->addMenu("&Preferences");

    autoSaveAction = prefereneMenu->addAction("Auto Save");
    autoSaveAction->setCheckable(true);
    autoSaveAction->setChecked(autoSave);
    connect(autoSaveAction, SIGNAL(triggered()), this, SLOT(setAutoSave()));

    showAxesAction = prefereneMenu->addAction("Show Axes");
    showAxesAction->setCheckable(true);
    showAxesAction->setChecked(showAxes);
    connect(showAxesAction, SIGNAL(triggered()), this, SLOT(setShowAxes()));


    QAction* zoomReset = settingsMenu->addAction("Reset Zoom Settings");
    connect(zoomReset, SIGNAL(triggered()), this, SLOT(zoom()));

    QAction* resetSettingsAction = settingsMenu->addAction("Reset Settings");
    connect(resetSettingsAction, SIGNAL(triggered()), this, SLOT(resetSettings()));

    QMenu* aboutMenu = menuBar()->addMenu(tr("&Help"));
    QAction* aboutAction = aboutMenu->addAction("About");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}
