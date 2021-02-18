#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_graphicsView(new QGraphicsView)
    , m_scene(new QGraphicsScene)
    , m_toolbox(new QToolBox)
{
    m_graphicsView->setScene(m_scene);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_graphicsView);

    QPushButton *pushButton = new QPushButton(tr("A button"));
    layout->addWidget(pushButton);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    this->setCentralWidget(widget);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_scene;
    delete m_graphicsView;
}
