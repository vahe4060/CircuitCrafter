#ifndef NODE_H
#define NODE_H
#include <QtWidgets>

class Edge;


class Node : public QGraphicsEllipseItem
{
    friend class Output_Node;
    friend class Input_Node;

public:
    Node(int xpos, int ypos, const int radius=10, QGraphicsItem* parent=nullptr);
    //virtual ~Node() = 0;

    enum { IN_NODE = UserType + 10,
           OUT_NODE  };

    int x() const;
    int y() const;
    int r() const;

    QList<Node*> nodes() const;

    void highlight(const QPen& pen);
    virtual void adjust();
    virtual int type() const = 0; //override { return Type; }
    virtual void addEdge(Node* e) = 0;
    virtual void removeEdge(Node* e) = 0;
    virtual bool areConnected(Node* other) = 0;

protected:
    int xpos, ypos;
    const int radius;
    QMap<Node*, Edge*> m_edges;
    QGraphicsLineItem* line = nullptr;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // NODE_H
