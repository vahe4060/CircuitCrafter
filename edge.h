#ifndef EDGE_H
#define EDGE_H
#include <QtWidgets>

class Node;

class Edge
{
public:
    Edge(Node *first, Node *second);
    void adjust();

private:
    QGraphicsLineItem *h_line = nullptr; // horizonal line
    QGraphicsLineItem *v_line = nullptr; // vertical line
    Node *m_left = nullptr;   // left node
    Node *m_right = nullptr;  // right node
};

#endif // EDGE_H
