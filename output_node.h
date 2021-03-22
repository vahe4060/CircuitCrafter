#ifndef OUTPUT_NODE_H
#define OUTPUT_NODE_H
#include <QtWidgets>
#include "node.h"
#include "edge.h"

class Output_Node: public Node
{
public:
    Output_Node(int xpos, int ypos, const int radius=10, QGraphicsItem* parent=nullptr);
    ~Output_Node();

    virtual int type() const override { return Node::output_node; }
    virtual void addEdge(Node* e) override;
    virtual void removeEdge(Node* e) override;
    virtual bool areConnected(Node* other) override;

};

#endif // OUTPUT_NODE_H
