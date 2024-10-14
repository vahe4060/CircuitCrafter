#include "graphicslineitem.h"
#include "edge.h"
#include "mainwindow.h"

GraphicsLineItem::GraphicsLineItem(TYPE t, QGraphicsItem *parent) : QGraphicsLineItem(parent)
  , m_t(t)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setPen(QPen(QBrush(MainWindow::WireColor()),  2));
}
GraphicsLineItem::GraphicsLineItem(TYPE t, const QLineF &line, QGraphicsItem *parent) : QGraphicsLineItem(parent)
  , m_t(t)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setPen(QPen(QBrush(MainWindow::WireColor()),  2));
    setLine(line);
}


/*
//void GraphicsLineItem::setLine(const QLineF &line)
//{
//    int lx = line.p1().x();
//    int rx = line.p2().x();
//    int ly = line.p1().y();
//    int ry = line.p2().y();
//    if(lx > rx)
//    {
//        int t = rx;
//        rx = lx;
//        lx = t;
//    }
//    if(ly > ry)
//    {
//        int t = ly;
//        ly = ry;
//        ry = t;
//    }
//
//    switch(m_t)
//    {
//        case HORIZONAL_LOWER:
//        {
//            QGraphicsLineItem::setLine(lx,ry, rx,ry);
//            break;
//        }
//        case HORIZONAL_UPPER:
//        {
//            QGraphicsLineItem::setLine(lx,ly, rx,ly);
//            break;
//        }
//        case VERTICAL_LEFT:
//        {
//            QGraphicsLineItem::setLine(lx,ly, lx,ry);
//            break;
//        }
//        case VERTICAL_RIGHT:
//        {
//            QGraphicsLineItem::setLine(rx,ly, rx,ry);
//            break;
//        }
//        default: break;
//    }
//}
*/

void GraphicsLineItem::keyPressEvent(QKeyEvent *event)
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
            delete parentItem();
            break;
        }
        default: break;
    }
}


QVariant GraphicsLineItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)
        {
            // do stuff if selected
            QPen pen(QBrush(Qt::green), 3);
            static_cast<Edge*>(parentItem())->highlight(pen);
        }
        else
        {
            // do stuff if not selected
            QPen pen(QBrush(MainWindow::WireColor()), 2);
            static_cast<Edge*>(parentItem())->highlight(pen);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}


QRectF GraphicsLineItem::boundingRect() const
{
    qreal extra = (pen().width() + 2) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


