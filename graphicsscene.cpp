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

void GraphicsScene::setCurrent(SceneItem::TYPE t)
{
    type = t;
    drawing = true;
}


void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() ==  Qt::Key_Escape)
    {
        drawing = false;
        MainWindow::View->setCursor(QCursor());
    }
    QGraphicsScene::keyPressEvent(event);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(drawing)
    {
        if(type == SceneItem::INPUT || type == SceneItem::OUTPUT)
            SceneItem* it = new Label(type, event->scenePos().x(), event->scenePos().y(), MainWindow::Center);
        else
            SceneItem* it = new Operator(type, event->scenePos().x(),event->scenePos().y(), MainWindow::Center);
    }

    QGraphicsScene::mousePressEvent((event));
}
