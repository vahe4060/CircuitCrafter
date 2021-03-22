#ifndef INPUT_NODE_H
#define INPUT_NODE_H
#include "node.h"
#include "edge.h"

class Input_Node: public Node
{
public:
    Input_Node(int xpos, int ypos, const int radius=10, QGraphicsItem* parent=nullptr);
    ~Input_Node();

    virtual int type() const override { return Node::input_node; }
    virtual void addEdge(Node* e) override;
    virtual void removeEdge(Node* e) override;
    virtual bool areConnected(Node* other) override;

};

#endif // OUTPUT_NODE_H
