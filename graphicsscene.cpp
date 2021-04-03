#include "graphicsscene.h"
#include "mainwindow.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{

}
GraphicsScene::GraphicsScene(const QRectF &sceneRect, QObject *parent): QGraphicsScene(sceneRect, parent)
{

}

GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent): QGraphicsScene(x, y, width, height, parent)
{

}

void GraphicsScene::loadAxes(bool show)
{
    if(show)
    {
        if(!m_AxisX)
            m_AxisX = addLine(2500,0,-2500,0, QPen(Qt::PenStyle::DotLine));
        if(!m_AxisY)
            m_AxisY = addLine(0,2500,0,-2500, QPen(Qt::PenStyle::DotLine));
    }
    else
    {
        if(m_AxisY)
            delete m_AxisY;
        if(m_AxisX)
            delete m_AxisX;
        m_AxisX = nullptr;
        m_AxisY = nullptr;
    }
}

void GraphicsScene::setCurrent(SceneItem::TYPE t)
{
    type = t;
    setDrawing(true);
    setErasing(false);
}

void GraphicsScene::setDrawing(bool d)
{
    drawing = d;
}

void GraphicsScene::setErasing(bool e)
{
    erasing = e;
}

void GraphicsScene::clear()
{
    // firstly delete Edges, then the operators/labels
    for(QGraphicsItem* it: MainWindow::instance()->Center()->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            delete it;
    }
    for(QGraphicsItem* it: MainWindow::instance()->Center()->childItems())
    {
        delete it;
    }
}

void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() ==  Qt::Key_Escape)
    {
        setDrawing(false);
        setErasing(false);
        MainWindow::instance()->View()->setCursor(QCursor());
    }
    QGraphicsScene::keyPressEvent(event);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(drawing)
    {
        if(type == SceneItem::INPUT || type == SceneItem::OUTPUT)
            SceneItem* it = new Label(type, event->scenePos().x(), event->scenePos().y(), MainWindow::instance()->Center());
        else
            SceneItem* it = new Operator(type, event->scenePos().x(),event->scenePos().y(), MainWindow::instance()->Center());
    }
    else if(erasing)
    {
        QGraphicsItem* it = itemAt(event->scenePos(), QTransform());
        if(it)
            delete it->parentItem();
    }
    else
    {
        QGraphicsScene::mousePressEvent((event));
    }
}

