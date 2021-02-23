#ifndef NODE_H
#define NODE_H
#include <vector>
#include <QtWidgets>

class Edge;

class Node : QGraphicsEllipseItem
{
public:
    Node(int xpos, int ypos);

    //void connect(Node* edge);
    //void adjust();
    int x() const;
    int y() const;
    void addEdge(Edge* e);

private:
    std::vector<Edge*> m_edges;
    int xpos, ypos;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // NODE_H
