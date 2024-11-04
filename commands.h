#ifndef COMMANDS_H
#define COMMANDS_H
#include <QUndoCommand>
#include <QGraphicsScene>
#include <QDebug>
#include "graphicssceneitem.h"
#include "graphicsscene.h"


class EraseItemCommand : public QUndoCommand
{
    SceneItem* m_item;
    SceneItem::TYPE m_type;
    QPointF m_pos;
public:
    EraseItemCommand(SceneItem *item)
        : m_item(item)
        , m_type(item->m_t)
        , m_pos(item->pos())
    {}
    void undo() override {
        if(m_type == SceneItem::INPUT || m_type == SceneItem::OUTPUT)
            m_item = new Label(m_type, m_pos.x(), m_pos.y(), GraphicsScene::centralItem());
        else
            m_item = new Operator(m_type, m_pos.x(), m_pos.y(), GraphicsScene::centralItem());
        // m_item->show(); /// TODO
    };
    void redo() override {
        delete m_item;
        m_item = nullptr;
        // m_item->hide();
    };
};


class EraseAllCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    EraseAllCommand() {}
    void undo() override {
        qDebug() << "Undoing erase all\n";
    }
    void redo() override {
        qDebug() << "Redoing erase all\n";
    }
};


class NewItemCommand : public QUndoCommand
{
    SceneItem* it;
    SceneItem::TYPE m_type;
    QPointF m_pos;
public:
    NewItemCommand(SceneItem::TYPE type, const QPointF &pos)
        : m_type(type)
        , m_pos(pos)
    {}
    void undo() override {
        delete it;
        it = nullptr;
    }
    void redo() override {
        if(m_type == SceneItem::INPUT || m_type == SceneItem::OUTPUT)
            it = new Label(m_type, m_pos.x(), m_pos.y(), GraphicsScene::centralItem());
        else
            it = new Operator(m_type, m_pos.x(), m_pos.y(), GraphicsScene::centralItem());
    }
};

class MoveItemCommand : public QUndoCommand
{
    SceneItem *m_item;
    QPointF m_newPos;
public:
    MoveItemCommand(SceneItem *it, const QPointF &newPos)
        : m_item(it)
        , m_newPos(newPos)
    {}
    void undo() override {
        QPointF currentPos = m_item->pos();
        m_item->setPos(m_newPos);
        m_newPos = currentPos;
    }
    void redo() override {
        QPointF currentPos = m_item->pos();
        m_item->setPos(m_newPos);
        m_newPos = currentPos;
    }
};


#endif // COMMANDS_H
