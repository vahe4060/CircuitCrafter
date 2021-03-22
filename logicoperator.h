#ifndef LOGICOPERATOR_H
#define LOGICOPERATOR_H
#include <QMap>
#include <QVector>

enum TYPE{
    NOT,
    AND,
    OR
};

class LogicOperator : public QGraphicsItemGroup
{
public:
    LogicOperator(TYPE t);
    virtual void execute();

private:
    QVector<bool> ins;
    QVector<bool> outs;
};

#endif // LOGICOPERATOR_H
