#include "labels.h"

Label::Label(TYPE t, int x, int y, QGraphicsItem* parent): SceneItem(t, x, y, parent)
{
    if(m_t == SceneItem::INPUT)
        m_outputs.push_back(new Output_Node(45, 8, 6, this));
    else
        m_inputs.push_back(new Input_Node(-11, 8, 6, this));


    m_pixmap = new GraphicsPixmapItem(QPixmap(":/Labels/src/" + SceneItem::types[t] + ".png"), this);
}


Label::Label(const int id, TYPE t, int x, int y, QGraphicsItem* parent): SceneItem(id, t, x, y, parent)
{
    if(m_t == SceneItem::INPUT)
        m_outputs.push_back(new Output_Node(45, 8, 6, this));
    else
        m_inputs.push_back(new Input_Node(-11, 8, 6, this));


    m_pixmap = new GraphicsPixmapItem(QPixmap(":/Labels/src/" + SceneItem::types[t] + ".png"), this);
}


void Label::execute()
{

}


