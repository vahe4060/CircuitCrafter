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
        qDebug() << "Undoing \n";
    };
    void redo() override {
        qDebug() << "Redoing \n";
    };
};

class EraseAllCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    EraseAllCommand() {}
    void undo() override {
        qDebug() << "Undoing \n";
    }
    void redo() override {
        qDebug() << "Redoing \n";
    }
};


class NewItemCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    NewItemCommand() {}
    void undo() override {
        qDebug() << "Undoing \n";
    }
    void redo() override {
        qDebug() << "Redoing \n";
    }
};

class MoveItemCommand : public QUndoCommand
{
    QGraphicsScene *myGraphicsScene;
public:
    MoveItemCommand() {}
    void undo() override {
        qDebug() << "Undoing Moveitem\n";
    }
    void redo() override {
        qDebug() << "Redoing Moveitem\n";
    }
};


#endif // COMMANDS_H
