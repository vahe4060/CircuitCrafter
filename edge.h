#ifndef EDGE_H
#define EDGE_H
#include <QtWidgets>
#include "graphicslineitem.h"

class Node;

class Edge : public QGraphicsItemGroup
{

public:
    Edge(Node *first, Node *second);
    ~Edge();
    void adjust();
    void highlight(QPen& pen);
    //virtual QRectF boundingRect() const override;
    //QPainterPath shape() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //void update(const QRectF &rect = QRectF());
//protected:
//    void advance(int step) override;

protected:
    QGraphicsLineItem *h_line1 = nullptr; // buttom horizonal line
    QGraphicsLineItem *h_line2 = nullptr; // upper horizonal line
    QGraphicsLineItem *v_line = nullptr;  // vertical line
    Node *m_left = nullptr;   // left node
    Node *m_right = nullptr;  // right node
};

#endif // EDGE_H
