#include "mainwindow.h"
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QShortcut>
#include <QMessageBox>

#ifndef EXPERIMENTAL

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
    , m_actAutoSave("Auto Save", this)
    , m_actShowAxes("Show Axes", this)
    , m_actMouse(QAction(QIcon(":/Tools/src/Mouse.png"), "Mouse", this))
    , m_actSave(QAction(QIcon(":/Tools/src/Save.png"), "Save", this))
    , m_actSaveAs(QAction(QIcon(":/Tools/src/SaveAs.png"), "Save As", this))
    , m_actNewFile(QAction(QIcon(":/Tools/src/NewFile.png"), "New File", this))
    , m_actOpenFile(QIcon(":/Tools/src/OpenFile.png"), "Open File", this)
    , m_actEraseAll(QAction(QIcon(":/Tools/src/EraseAll.png"), "Erase All", this))
    , m_actZoomIn(QAction(QIcon(":/Tools/src/ZoomIn.png"), "Zoom In", this))
    , m_actZoomOut(QAction(QIcon(":/Tools/src/ZoomOut.png"), "Zoom Out", this))
    , m_actZoomReset(QAction(QIcon(":/Tools/src/ZoomReset.png"), "Zoom Reset", this))
    , m_actCompile("Convert to Verilog", this)
    , m_actCheck(QIcon(":/Tools/src/Check.png"), "Check Scheme", this)
    , m_actResetSettings("Reset Settings", this)
    , m_actAbout("About", this)
    , m_actElem_NOT(QAction(QIcon(":/Operators/src/NOT.png"), "Mouse (ESC)", this))
    , m_actElem_AND(QAction(QIcon(":/Operators/src/AND.png"), "Mouse (ESC)", this))
    , m_actElem_OR(QAction(QIcon(":/Operators/src/OR.png"), "Mouse (ESC)", this))
    , m_actElem_XOR(QAction(QIcon(":/Operators/src/XOR.png"), "Mouse (ESC)", this))
    , m_actElem_NAND(QAction(QIcon(":/Operators/src/NAND.png"), "Mouse (ESC)", this))
    , m_actElem_NOR(QAction(QIcon(":/Operators/src/NOR.png"), "Mouse (ESC)", this))
    , m_actElem_XNOR(QAction(QIcon(":/Operators/src/XNOR.png"), "Mouse (ESC)", this))
    , m_actElem_IN(QAction(QIcon(":/Labels/src/IN.png"), "Mouse (ESC)", this))
    , m_actElem_OUT(QAction(QIcon(":/Labels/src/OUT.png"), "Mouse (ESC)", this))
{
    resize(860,640);
    setWindowTitle("");
    QWidget *widget = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    m_Scene = new GraphicsScene(QRectF(-2500, -2500, 5000, 5000), this);
    m_View = new GraphicsView(m_Scene);

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
    delete m_Scene;
    delete m_View;
    delete m_toolbar_operators;
    delete m_toolbar_tools;
    delete m_instance;
}

int MainWindow::popUpDialog(const QString &name,
                const QString &text,
                QMessageBox::Icon icon,
                QMessageBox::StandardButtons buttons
                )
{
    return QMessageBox(icon, name, text, buttons, this).exec();
}

bool MainWindow::check()
{
    save();

    QList<QGraphicsItem*> items = GraphicsScene::centralItem()->childItems();
    for(int i=items.size() - 1; i >= 0; i--)
        if(items[i]->type() == Edge::TYPE::EDGE)
        {
            items.removeAt(i);
        }

    int output_count = 0;
    int input_count = 0;
    for(QGraphicsItem* i: items)
    {
        SceneItem* it = static_cast<SceneItem*>(i);

        if(it->type() != SceneItem::TYPE::INPUT && it->isDanglingInput())
        {
            popUpDialog("Editor",
                        "Compilation failed. Dangling input detected: "
                            + it->toString() + " " + QString::number(it->id()),
                        QMessageBox::Warning,
                        QMessageBox::Ok);
            QPen p(Qt::red);
            p.setWidth(4);
            it->setSelected(true);
            it->highlight(p);
            return false;
        }
        else if(it->type() != SceneItem::TYPE::OUTPUT && it->isDanglingOutput())
        {
            popUpDialog("Editor", "Compilation failed. Dangling output detected: "
                                  + it->toString() + " " + QString::number(it->id()),
                        QMessageBox::Warning,
                        QMessageBox::Ok);
            QPen p(Qt::red);
            p.setWidth(4);
            it->setSelected(true);
            it->highlight(p);
            return false;
        }

        switch(i->type())
        {
            case SceneItem::TYPE::OUTPUT:
                output_count++;
                break;
            case SceneItem::TYPE::INPUT:
                input_count++;
                break;
            default: break;
        }
    }

    if(!output_count)
    {
        popUpDialog("Error",
                    "Compilation failed. Please provide output label(s) for your scheme",
                    QMessageBox::Warning,
                    QMessageBox::Ok);
        return false;
    }
    if(!input_count)
    {
        popUpDialog("Error",
                    "Compilation failed. Please provide input label(s) for your scheme",
                    QMessageBox::Warning,
                    QMessageBox::Ok);
        return false;
    }

    return true;
}

void MainWindow::compile()
{
    if(!check())
    {
        return;
    }

    QList<QGraphicsItem*> items = GraphicsScene::centralItem()->childItems();

    for(int i=items.size() - 1; i >= 0; i--)
        if(items[i]->type() == Edge::TYPE::EDGE)
        {
            items.removeAt(i);
        }

    Verilog_Parser p(currentPath);
    for(QGraphicsItem* i: items)
    {
        SceneItem* it = static_cast<SceneItem*>(i);
        if(it->type() == SceneItem::TYPE::INPUT)
            p.input(it);
        else if(it->type() == SceneItem::TYPE::OUTPUT)
            p.output(it);
        else
        {
            p.wire(it);
            p.operand(it);
        }
    }
    p.parse();
}

void MainWindow::newDocument()
{
    if(updated)
    {
        auto reply = popUpDialog("Editor", "Save current file?",
                                 QMessageBox::Question,
                                 QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
           save();
        else if(reply == QMessageBox::Cancel)
           return;
    }
    m_Scene->clear();
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
            auto reply = popUpDialog("Editor", "Save changes before exit?",
                                     QMessageBox::Question,
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
    m_actShowAxes.setChecked(true);
    loadAxes();

    autoSave = false;
    m_actShowAxes.setChecked(false);

    wireColor = Qt::black;
    QPen pen(QBrush(wireColor), 2);
    for(QGraphicsItem* it:GraphicsScene::centralItem()->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            static_cast<Edge*>(it)->highlight(pen);
    }
}

void MainWindow::setDrawingObject(SceneItem::TYPE t)
{
    m_Scene->setCurrent(t);

    if(t == SceneItem::INPUT || t == SceneItem::OUTPUT)
        m_View->setCursor(QCursor(QPixmap(":/Labels/src/" + SceneItem::types[t] + ".png"), 0,0));
    else
        m_View->setCursor(QCursor(QPixmap(":/Operators/src/" + SceneItem::types[t] + ".png"), 0,0));
}

void MainWindow::stopDrawingObject()
{
    m_Scene->setDrawing(false);
    m_View->setCursor(QCursor());
}

void MainWindow::zoom(int zoomin)
{
    if(zoomin > 0)
        m_View->scale(1.1, 1.1);
    else if(zoomin < 0)
        m_View->scale(0.90909, 0.90909);
    else
        m_View->resetTransform();
}

void MainWindow::eraseAll()
{
    auto reply = popUpDialog("Editor", "Are you sure you want to erase everything?",
                             QMessageBox::Question,
                             QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
        m_Scene->clear();
}

void MainWindow::save()
{
    if(currentPath == "")
    {
        QString fileName = QFileDialog::getSaveFileName(nullptr, QString(), QString(), QString());
        if(fileName == "")
            return;
        currentPath = fileName;
    }

    QList<QGraphicsItem*> items = GraphicsScene::centralItem()->childItems();
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
            SceneItem *it = static_cast<SceneItem*>(i);

            QJsonObject RootObject;
            RootObject["id"] = it->id();
            RootObject["type"] = it->type();

            QJsonObject pos;
            pos["x"] = int(i->pos().x());
            pos["y"] = int(i->pos().y());
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
        auto reply = popUpDialog("Editor", "Save current file?",
                                 QMessageBox::Question,
                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
        {
           save();
        }
        else if(reply == QMessageBox::Cancel)
        {
           return;
        }
    }
    QString fileName = QFileDialog::getOpenFileName(nullptr, QString(), QString(), QString());
    if(fileName == "")
        return;

    m_Scene->clear();
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
            new Label(id, t, x, y, GraphicsScene::centralItem());
        else
            new Operator(id, t, x, y, GraphicsScene::centralItem());
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
    popUpDialog("Editor",
                "\tQt version:           6.7.3",
                QMessageBox::Question,
                QMessageBox::Ok);
}

void MainWindow::setToolBar()
{
    m_toolbar_operators = addToolBar(tr("Operators"));
    m_toolbar_tools = addToolBar(tr("Tools"));

    connect(&m_actMouse, SIGNAL(triggered()), this, SLOT(stopDrawingObject()));
    connect(&m_actEraseAll, SIGNAL(triggered()), this, SLOT(eraseAll()));
    m_toolbar_tools->addAction(&m_actMouse);
    m_toolbar_tools->addSeparator();
    m_toolbar_tools->addAction(m_Scene->getUndoAction());
    m_toolbar_tools->addAction(m_Scene->getRedoAction());
    m_toolbar_tools->addSeparator();
    m_toolbar_tools->addAction(&m_actSave);
    m_toolbar_tools->addAction(&m_actCheck);
    m_toolbar_tools->addAction(&m_actEraseAll);
    m_toolbar_tools->addSeparator();
    m_toolbar_tools->addActions({&m_actZoomIn, &m_actZoomOut, &m_actZoomReset});

    // APPROACH 1
    // mapping signal to slot with non-void arguments
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(&m_actZoomIn, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(&m_actZoomOut, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(&m_actZoomReset, SIGNAL(triggered()), signalMapper, SLOT (map()));
    signalMapper->setMapping(&m_actZoomReset, 0);
    signalMapper->setMapping(&m_actZoomIn, 1);
    signalMapper->setMapping(&m_actZoomOut, -1);
    connect(signalMapper, &QSignalMapper::mappedInt, this, &MainWindow::zoom);
    // APPROACH 2
    // mapping signal to slot with non-void arguments
    m_toolbar_operators->addActions({&m_actElem_NOT, &m_actElem_AND, &m_actElem_OR,
                                     &m_actElem_XOR, &m_actElem_NAND, &m_actElem_NOR,
                                     &m_actElem_XNOR, &m_actElem_IN, &m_actElem_OUT});
    connect(&m_actElem_NOT, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::NOT); });
    connect(&m_actElem_AND, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::AND); });
    connect(&m_actElem_OR, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::OR); });
    connect(&m_actElem_XOR, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::XOR); });
    connect(&m_actElem_NAND, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::NAND); });
    connect(&m_actElem_NOR, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::NOR); });
    connect(&m_actElem_XNOR, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::XNOR); });
    connect(&m_actElem_IN, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::INPUT); });
    connect(&m_actElem_OUT, &QAction::triggered, this, [this] { setDrawingObject(SceneItem::TYPE::OUTPUT); });
}

void MainWindow::setMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu* itemMenu = menuBar()->addMenu(tr("&Project"));
    QMenu* settingsMenu = menuBar()->addMenu(tr("&Settings"));
    QMenu* prefereneMenu = settingsMenu->addMenu("&Preferences");
    QMenu* aboutMenu = menuBar()->addMenu(tr("&Help"));

    fileMenu->addAction(&m_actNewFile);
    fileMenu->addAction(&m_actOpenFile);
    fileMenu->addSeparator();
    fileMenu->addAction(&m_actSave);
    fileMenu->addAction(&m_actSaveAs);
    connect(&m_actNewFile, SIGNAL(triggered()), this, SLOT(newDocument()));
    connect(&m_actOpenFile, SIGNAL(triggered()), this, SLOT(load()));
    connect(&m_actSave, SIGNAL(triggered()), this, SLOT(save()));

    itemMenu->addAction(m_Scene->getUndoAction());
    itemMenu->addAction(m_Scene->getRedoAction());
    itemMenu->addSeparator();
    itemMenu->addAction(&m_actCompile);
    itemMenu->addAction(&m_actCheck);
    connect(&m_actCompile, SIGNAL(triggered()), this, SLOT(compile()));
    connect(&m_actCheck, SIGNAL(triggered()), this, SLOT(check()));

    prefereneMenu->addAction(&m_actAutoSave);
    prefereneMenu->addAction(&m_actShowAxes);
    m_actAutoSave.setCheckable(true);
    m_actAutoSave.setChecked(autoSave);
    m_actShowAxes.setCheckable(true);
    m_actShowAxes.setChecked(showAxes);
    connect(&m_actShowAxes, SIGNAL(triggered()), this, SLOT(setShowAxes()));
    connect(&m_actAutoSave, SIGNAL(triggered()), this, SLOT(setAutoSave()));

    settingsMenu->addAction(&m_actZoomReset);
    settingsMenu->addAction(&m_actResetSettings);
    connect(&m_actZoomReset, SIGNAL(triggered()), this, SLOT(zoom()));
    connect(&m_actResetSettings, SIGNAL(triggered()), this, SLOT(resetSettings()));

    aboutMenu->addAction(&m_actAbout);
    connect(&m_actAbout, SIGNAL(triggered()), this, SLOT(about()));
}

#else



#endif
