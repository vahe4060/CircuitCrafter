#ifndef LOGIC_OPERATOR_H
#define LOGIC_OPERATOR_H
#include <QGraphicsItemGroup>
#include "input_node.h"
#include "output_node.h"
#include "graphicspixmapitem.h"

class SceneItem: public QGraphicsItemGroup
{
public:
    enum TYPE{
        INPUT = UserType + 30,
        OUTPUT,
        NOT,
        AND,
        OR,
        XOR,
        NAND,
        NOR,
        XNOR
    };

    explicit SceneItem(TYPE t, int x, int y, QGraphicsItem* parent=nullptr);
    virtual ~SceneItem();

    virtual void highlight(QPen& pen);
    virtual void setPos(QPointF pos);
    virtual int type() const override { return m_t; }
    virtual void execute() = 0;

protected:
    QVector<Input_Node*> m_inputs;
    QVector<Output_Node*> m_outputs;
    GraphicsPixmapItem* m_pixmap = nullptr;
    TYPE m_t;

    static QMap<TYPE, QString> types;
};

#endif // LOGIC_OPERATOR_H
