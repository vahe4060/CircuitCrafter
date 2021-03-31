#include "operators.h"

Operator::Operator(TYPE t, int x, int y, QGraphicsItem* parent) : SceneItem(t, x, y, parent)
{
    if(m_t == TYPE::NOT)
    {
        m_inputs.push_back(new Input_Node(-12, 16, 6, this));
        m_outputs.push_back(new Output_Node(57, 16, 6, this));
    }
    else
    {
        m_inputs.push_back(new Input_Node(-12, 5, 6, this));
        m_inputs.push_back(new Input_Node(-12, 26, 6, this));
        m_outputs.push_back(new Output_Node(63, 16, 6, this));
    }
    m_pixmap = new GraphicsPixmapItem(QPixmap(":/Operators/images/" + SceneItem::types[t] + ".png"), this);
}


Operator::Operator(const int id, TYPE t, int x, int y, QGraphicsItem* parent): SceneItem(id, t, x, y, parent)
{
    if(m_t == TYPE::NOT)
    {
        m_inputs.push_back(new Input_Node(-12, 16, 6, this));
        m_outputs.push_back(new Output_Node(57, 16, 6, this));
    }
    else
    {
        m_inputs.push_back(new Input_Node(-12, 5, 6, this));
        m_inputs.push_back(new Input_Node(-12, 26, 6, this));
        m_outputs.push_back(new Output_Node(63, 16, 6, this));
    }
    m_pixmap = new GraphicsPixmapItem(QPixmap(":/Operators/images/" + SceneItem::types[t] + ".png"), this);
}


void Operator::execute()
{

}
