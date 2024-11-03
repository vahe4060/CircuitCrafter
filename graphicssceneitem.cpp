#include "graphicssceneitem.h"
#include "mainwindow.h"

QMap<SceneItem::TYPE, QString> SceneItem::types = {
    {SceneItem::TYPE::NOT,    "NOT"},
    {SceneItem::TYPE::AND,    "AND"},
    {SceneItem::TYPE::OR,     "OR"},
    {SceneItem::TYPE::XOR,    "XOR"},
    {SceneItem::TYPE::NAND,   "NAND"},
    {SceneItem::TYPE::NOR,    "NOR"},
    {SceneItem::TYPE::XNOR,   "XNOR"},
    {SceneItem::TYPE::INPUT,  "IN"},
    {SceneItem::TYPE::OUTPUT, "OUT"}
};

int SceneItem::id_count = 0;

SceneItem::SceneItem(TYPE t, int x, int y, QGraphicsItem* parent) : QGraphicsItemGroup(parent)
   , m_t(t)
   , m_id(++SceneItem::id_count)
{
    QGraphicsItemGroup::setPos(x,y);
    setHandlesChildEvents(false);
    MainWindow::instance()->setUpdatedFlag();
}

SceneItem::SceneItem(const int id, TYPE t, int x, int y, QGraphicsItem* parent) : QGraphicsItemGroup(parent)
   , m_t(t)
   , m_id(id)
{
    QGraphicsItemGroup::setPos(x,y);
    setHandlesChildEvents(false);
    if (m_id > SceneItem::id_count)
        SceneItem::id_count = m_id;
    MainWindow::instance()->setUpdatedFlag();
}

SceneItem::~SceneItem()
{
    delete m_pixmap;

    for(Node* i : m_inputs)
    {
        delete i;
    }
    for(Node* i : m_outputs)
    {
        delete i;
    }

    MainWindow::instance()->setUpdatedFlag();
}

void SceneItem::setSelected(bool state)
{
    m_pixmap->setSelected(state);
}

QVector<SceneItem*> SceneItem::inputs() const
{
    QVector<SceneItem*> ins;
    ins.reserve(m_inputs.size());
    for(Node* i: m_inputs)
        for(Node* j: i->nodes())
            ins.push_back(static_cast<SceneItem*>(j->parentItem()));
    return ins;
}

QVector<SceneItem*> SceneItem::outputs() const
{
    QVector<SceneItem*> outs;
    for(Node* i: m_outputs)
        for(Node* j: i->nodes())
            outs.push_back(static_cast<SceneItem*>(j->parentItem()));
    return outs;
}


void SceneItem::highlight(QPen &pen)
{
    for(Node* i : m_inputs)
    {
        i->highlight(pen);
    }
    for(Node* i : m_outputs)
    {
        i->highlight(pen);
    }
}

void SceneItem::setPos(QPointF pos)
{
    QGraphicsItemGroup::setPos(pos);

    for(Node* i : m_inputs)
    {
        i->adjust();
    }
    for(Node* i : m_outputs)
    {
        i->adjust();
    }

    MainWindow::instance()->setUpdatedFlag();
}

bool SceneItem::isDanglingInput() const
{
    for(Node* i: m_inputs)
        if(i->nodes().isEmpty())
            return true;
    return false;
}

bool SceneItem::isDanglingOutput() const
{
    for(Node* i: m_outputs)
        if(i->nodes().isEmpty())
            return true;
    return false;
}
