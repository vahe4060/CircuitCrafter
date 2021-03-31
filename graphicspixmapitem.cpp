#include "graphicspixmapitem.h"
#include "graphicssceneitem.h"
#include "mainwindow.h"

GraphicsPixmapItem::GraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

QVariant GraphicsPixmapItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)
        {
            // do stuff if selected
            QPen pen(QBrush(Qt::green), 3);
            static_cast<SceneItem*>(parentItem())->highlight(pen);
        }
        else
        {
            // do stuff if not selected
            QPen pen(QBrush(Qt::GlobalColor(MainWindow::WireColor())), 2);
            static_cast<SceneItem*>(parentItem())->highlight(pen);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}


void GraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos = event->scenePos() - this->scenePos();
}


void GraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    SceneItem* p = static_cast<SceneItem*>(parentItem());
    p->setPos(event->scenePos() - m_mousePos);
}


void GraphicsPixmapItem::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
        {
            setSelected(false);
            break;
        }
        case Qt::Key_Delete:
        {
            delete this->parentItem();
            break;
        }
        case Qt::Key_Up:
        {
            SceneItem* p = static_cast<SceneItem*>(parentItem());
            int x = int(p->scenePos().x());
            int y = int(p->scenePos().y());
            x -= x % 10;
            y -= y % 10;
            p->setPos(QPointF(x,y) - QPointF(0,10));
            break;
        }
        case Qt::Key_Down:
        {
            SceneItem* p = static_cast<SceneItem*>(parentItem());
            int x = int(p->scenePos().x());
            int y = int(p->scenePos().y());
            x -= x % 10;
            y -= y % 10;
            p->setPos(QPointF(x,y) + QPointF(0,10));
            break;
        }
        case Qt::Key_Left:
        {
            SceneItem* p = static_cast<SceneItem*>(parentItem());
            int x = int(p->scenePos().x());
            int y = int(p->scenePos().y());
            x -= x % 10;
            y -= y % 10;
            p->setPos(QPointF(x,y) - QPointF(10,0));
            break;
        }
        case Qt::Key_Right:
        {
            SceneItem* p = static_cast<SceneItem*>(parentItem());
            int x = int(p->scenePos().x());
            int y = int(p->scenePos().y());
            x -= x % 10;
            y -= y % 10;
            p->setPos(QPointF(x,y) + QPointF(10,0));
            break;
        }

        default: break;
    }
}
