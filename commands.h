#ifndef COMMANDS_H
#define COMMANDS_H
#include <QUndoCommand>
#include <QGraphicsScene>
#include <QDebug>

class EraseItemCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    EraseItemCommand() {}
    void undo() override {
        qDebug() << "Undoing erase item\n";
    };
    void redo() override {
        qDebug() << "Redoing erase item\n";
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
    QGraphicsScene *myGraphicsScene;
public:
    NewItemCommand() {}
    void undo() override {
        qDebug() << "Undoing new item\n";
    }
    void redo() override {
        qDebug() << "Redoing new item\n";
    }
};

class MoveItemCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    MoveItemCommand() {}
    void undo() override {
        qDebug() << "Undoing move item\n";
    }
    void redo() override {
        qDebug() << "Redoing move item\n";
    }
};


#endif // COMMANDS_H
