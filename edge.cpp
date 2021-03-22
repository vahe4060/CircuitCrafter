#include "edge.h"
#include "mainwindow.h"


Edge::Edge(Node *left, Node *right) : QGraphicsItemGroup(MainWindow::Center)
  , m_left(left)
  , m_right(right)
{
    // check if left and right are in wrong order, and swap them if neccessary
    if(m_left->x() > m_right->x())
    {
        m_left = right;
        m_right = left;
    }

    //MainWindow::Scene->addItem(this);
    h_line1 = new GraphicsLineItem(GraphicsLineItem::HORIZONAL_LOWER, this);
    h_line2 = new GraphicsLineItem(GraphicsLineItem::HORIZONAL_UPPER, this);
    v_line  = new GraphicsLineItem(GraphicsLineItem::VERTICAL_LEFT, this);

    //this->addToGroup(h_line1);
    //this->addToGroup(h_line2);
    //this->addToGroup(v_line);

    adjust();
    setZValue(1);
    setHandlesChildEvents(false);
}

Edge::~Edge()
{
    m_left->removeEdge(m_right);

    MainWindow::Scene->removeItem(h_line1);
    MainWindow::Scene->removeItem(h_line2);
    MainWindow::Scene->removeItem(v_line);

    //or  m_right->removeEdge(m_left);
    delete h_line1;
    delete h_line2;
    delete v_line;
}


void Edge::highlight(QPen &pen)
{
    for(QGraphicsItem* i: childItems())
    {
        static_cast<QGraphicsLineItem*>(i)->setPen(pen);
    }
}


void Edge::adjust()
{
    int x1 = m_left->x() +  m_left->r();
    int y1 = m_left->y() + m_left->r();
    int x2 = m_right->x() + m_right->r();
    int y2 = m_right->y() + m_right->r();

    int lx = (x1 < x2) ? x1 : x2;
    int rx = x1 + x2 - lx;
    int ly = (y1 < y2) ? y1 : y2;
    int ry = y1 + y2 - ly;


    bool adjusted = false;

    for(int x = lx; x < rx; x += 10)
    {
        bool AreaIsBusy = false;

        QList<QGraphicsItem*> items = MainWindow::Scene->items(QRectF(QPointF(x,ly), QPointF(x+5,ry)));
        for(int i =0; i < items.size(); i++)
        {
            if(items[i]->type() == GraphicsLineItem::VERTICAL_LEFT) // || items[i]->type() == GraphicsLineItem::VERTICAL_RIGHT
            {
                if(static_cast<Edge*>(items[i]->parentItem())->m_left != m_left)
                {
                    AreaIsBusy = true;
                    break;
                }
            }
            else if(items[i]->type() == Node::input_node || items[i]->type() == Node::output_node)
            {
                AreaIsBusy = true;
                break;
            }
        }

        if(!AreaIsBusy)
        {
            if(y1 == y2)
            {
                h_line1->setLine(QLineF(x1 + m_left->r(), y1, x2 - m_right->r(), y2));
                h_line2->setLine(QLineF(0,0,0,0));
                v_line->setLine(QLineF(0,0,0,0));
            }
            else if(x1 == x2)
            {
                h_line1->setLine(QLineF(0,0,0,0));
                h_line2->setLine(QLineF(0,0,0,0));
                v_line->setLine(QLineF(x1, ly + m_left->r(), x1, ry - m_right->r()));
            }
            else if(x == x1)
            {
                h_line1->setLine(QLineF(0,0,0,0));
                h_line2->setLine(QLineF(x, y2, x2 - m_right->r(), y2));
                if(y1 < y2)
                    v_line->setLine(QLineF(x, y1 + m_left->r(), x, y2));
                else
                    v_line->setLine(QLineF(x, y1 - m_left->r(), x, y2));
            }
            else
            {
                h_line1->setLine(QLineF(x1 + m_left->r(), y1, x, y1));
                h_line2->setLine(QLineF(x, y2, x2 - m_right->r(), y2));
                v_line->setLine(QLineF(x, y1, x, y2));
            }
            adjusted = true;
            break;
        }
    }

    if(!adjusted)
    {
        h_line2->setLine(QLineF(0,0,0,0));

        if(y1 == y2)
        {
            h_line1->setLine(QLineF(x1 + m_left->r(), y1, x2 - m_right->r(), y2));
        }
        else if(x1 == x2)
        {
            v_line->setLine(QLineF(x1, y1 + m_left->r(), x2, y2 - m_right->r()));
        }
        else if(y1 > y2)
        {
            h_line1->setLine(QLineF(x1 + m_left->r(), y1, x2, y1));
            v_line->setLine(QLineF(x2, y1, x2, y2 + m_right->r()));
        }
        else if(y1 < y2)
        {
            h_line1->setLine(QLineF(x1 + m_left->r(), y1, x2, y1));
            v_line->setLine(QLineF(x2, y1, x2, y2 - m_right->r()));
        }
        else
        {
            qDebug() << "something wrong in Edge::adjust";
        }
    }

}



