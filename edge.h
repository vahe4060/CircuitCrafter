#ifndef EDGE_H
#define EDGE_H
#include <QtWidgets>
#include "graphicslineitem.h"

class Node;

class Edge : public QGraphicsItemGroup
{
public:
    enum TYPE
    {
        EDGE = UserType + 5
    };

    Edge(Node *first, Node *second);
    ~Edge();
    Node* left() const { return m_left; }
    Node* right() const { return m_right; }
    void adjust();
    void highlight(const QPen& pen);

    virtual int type() const override { return TYPE::EDGE; }

protected:
    QGraphicsLineItem *h_line1 = nullptr; // buttom horizonal line
    QGraphicsLineItem *h_line2 = nullptr; // upper horizonal line
    QGraphicsLineItem *v_line = nullptr;  // vertical line
    Node *m_left = nullptr;   // left node
    Node *m_right = nullptr;  // right node
};

#endif // EDGE_H
