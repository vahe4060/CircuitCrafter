#ifndef LOGIC_OPERATOR_H
#define LOGIC_OPERATOR_H
#include <QGraphicsItemGroup>
#include "input_node.h"
#include "output_node.h"
#include "graphicspixmapitem.h"
#include <QPointF>
#include <QObject>
#include <QGraphicsItemGroup>

class SceneItem: public QGraphicsItemGroup
{
public:
    enum TYPE {
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
    static QMap<TYPE, QString> types;

    SceneItem(TYPE t, int x, int y, QGraphicsItem* parent=nullptr);
    SceneItem(const int id, TYPE t, int x, int y, QGraphicsItem* parent=nullptr);

    virtual ~SceneItem();

    void setSelected(bool state);
    // virtual void disable(); // TODO
    // virtual void enable(); // TODO
    virtual void highlight(QPen& pen);
    virtual void setPos(QPointF pos);
    virtual int type() const override { return m_t; }
    virtual int id() const { return m_id; }
    virtual void execute() = 0;

    QString toString() const { return SceneItem::types[m_t]; }
    QVector<SceneItem*> inputs() const;
    QVector<SceneItem*> outputs() const;
    bool isDanglingInput() const;
    bool isDanglingOutput() const;

protected:
    static int id_count;

    QVector<Input_Node*> m_inputs;
    QVector<Output_Node*> m_outputs;
    GraphicsPixmapItem* m_pixmap = nullptr;
    TYPE m_t;
    const int m_id;

    friend class EraseItemCommand;
    friend class NewItemCommand;
};

#endif // LOGIC_OPERATOR_H
