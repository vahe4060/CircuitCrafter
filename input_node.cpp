#include "input_node.h"


Input_Node::Input_Node(int xpos, int ypos, const int radius, QGraphicsItem* parent) :
    Node(xpos, ypos, radius, parent)
{
    this->setBrush(QBrush(Qt::green));
    this->setPen(QPen(Qt::green));
}

Input_Node::~Input_Node()
{
    if(!m_edges.empty())
        delete m_edges.first();
        //removeEdge(m_edges.firstKey());

}

void Input_Node::addEdge(Node *other)
{
    if(!areConnected(other) && other->type() == Node::output_node)
    {
        if(!m_edges.empty())
        {
            //Node* it = m_edges.firstKey();
            //removeEdge(it);
            delete m_edges.first();
        }

        Edge* e = new Edge(this, other);
        m_edges[other] = e;
        other->m_edges[this] = e;
    }
}

void Input_Node::removeEdge(Node* other)
{
    if(areConnected(other))
    {
        Edge* e = m_edges.first();
        m_edges.clear();
        other->removeEdge(this);
        //delete e;
    }
}

bool Input_Node::areConnected(Node *other)
{
    if(m_edges.find(other) == m_edges.end())
        return false;
    return true;
}
