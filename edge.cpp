#include "edge.h"
#include "mainwindow.h"

Edge::Edge(Node *left, Node *right) :
    m_left(left)
  , m_right(right)
{
    // check if left and right are in wrong order, and swap them if neccessary
    if(m_left->x() > m_right->x())
    {
        m_left = right;
        m_right = left;
    }

    h_line = new QGraphicsLineItem;
    v_line = new QGraphicsLineItem;

    MainWindow::Scene->addItem(h_line);
    MainWindow::Scene->addItem(v_line);

    adjust();

    m_left->addEdge(this);
    m_right->addEdge(this);
}


void Edge::adjust()
{
    int x1 = m_left->x();
    int y1 = m_left->y();
    int x2 = m_right->x();
    int y2 = m_right->y();

    h_line->setLine(x1, y1, x2, y1);
    v_line->setLine(x2, y2, x2, y1);
}
