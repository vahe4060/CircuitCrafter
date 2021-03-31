#include "node.h"
#include "mainwindow.h"

Node::Node(int xpos, int ypos, const int radius, QGraphicsItem* parent) : QGraphicsEllipseItem(0, 0, 2*radius, 2*radius, parent)
    , xpos(xpos)
    , ypos(ypos)
    , radius(radius)
{
    QGraphicsEllipseItem::setPos(QPointF(xpos, ypos));
    setZValue(3);
    //setFlag(ItemIsMovable);
    //MainWindow::instance()->Scene()->addItem(this);
    QGraphicsLineItem* line = new QGraphicsLineItem;
}

void Node::adjust()
{
    for(QMap<Node*, Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); ++it)
        it.value()->adjust();
}

void Node::highlight(QPen& pen)
{
    for(auto*i: m_edges)
    {
        i->highlight(pen);
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //xpos = event->scenePos().x();
    //ypos = event->scenePos().y();
    //
    //for(size_t i = 0; i < m_edges.size(); i++)
    //{
    //    m_edges[i]->adjust();
    //}
    //QGraphicsItem::mouseMoveEvent(event);
    int cx = event->scenePos().x();
    int cy = event->scenePos().y();

    line->setLine(x() + radius, y() + radius, cx, cy);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    line = new QGraphicsLineItem;
    MainWindow::instance()->Scene()->addItem(line);

    //qDebug() << "............";
    //for(auto* i: MainWindow::instance()->Scene()->items())
    //{
    //    qDebug() << i->type() << i;
    //}
    //qDebug() << "............";
    //std::cout<<x()<<" "<<y()<<"\n";
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    MainWindow::instance()->Scene()->removeItem(line);
    delete line;

    int cx = event->scenePos().x();
    int cy = event->scenePos().y();

    QGraphicsItem *it = MainWindow::instance()->Scene()->itemAt(cx, cy, QTransform());
    if(it && (it->type() == Node::IN_NODE || it->type() == Node::OUT_NODE))
    {
        Node* target = static_cast<Node*>(it);
        addEdge(target);
    }

    //qDebug() << "-------------------";
    //for(auto* i: MainWindow::instance()->Scene()->items())
    //{
    //    qDebug() << i->type() << i;
    //}
    //qDebug() << "-------------------";
}


int Node::x() const
{
    return scenePos().x(); //xpos;
}

int Node::y() const
{
    return scenePos().y(); //ypos;
}

int Node::r() const
{
    return radius;
}

