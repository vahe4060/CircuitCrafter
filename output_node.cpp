#include "output_node.h"

Output_Node::Output_Node(int xpos, int ypos, const int radius, QGraphicsItem* parent) :
    Node(xpos, ypos, radius, parent)
{
    this->setBrush(QBrush(Qt::red));
    this->setPen(QPen(Qt::red));
}

Output_Node::~Output_Node()
{
    for(Edge* i: m_edges.values())
    {
        delete i;
        //removeEdge(i);
    }
}


void Output_Node::addEdge(Node *other)
{
    if(!areConnected(other) && other->type() == Node::input_node)
    {
        //if(!other->m_edges.empty())
        //{
        //    other->m_edges.firstKey()->removeEdge(other);
        //}
        //
        //Edge* e = new Edge(this, other);
        //m_edges[other] = e;
        //other->m_edges[this] = e;

        other->addEdge(this);
    }
}

void Output_Node::removeEdge(Node* other)
{
    if(areConnected(other))
    {
        QMap<Node*, Edge*>::iterator it = m_edges.find(other);
        m_edges.erase(it);
        other->removeEdge(this);
    }
}

bool Output_Node::areConnected(Node *other)
{
    if(m_edges.find(other) == m_edges.end())
        return false;
    return true;
}
