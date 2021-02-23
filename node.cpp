#include "node.h"
#include "mainwindow.h"
#include <iostream>

Node::Node(int xpos, int ypos):
    QGraphicsEllipseItem(xpos, ypos, 10, 10)
  , xpos(xpos)
  , ypos(ypos)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true );

    MainWindow::Scene->addItem(this);

}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    xpos = pos().x();           // bug here
    ypos = pos().y();           // bug here

    for(size_t i = 0; i < m_edges.size(); i++)
    {
        m_edges[i]->adjust();
    }
    QGraphicsItem::mouseMoveEvent(event);

}

void Node::addEdge(Edge *e)
{
    m_edges.push_back(e);
}

int Node::x() const
{
    return xpos;
}

int Node::y() const
{
    return ypos;
}
