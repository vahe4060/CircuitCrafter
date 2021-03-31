#ifndef OPERATORS_H
#define OPERATORS_H
#include "graphicssceneitem.h"

class Operator: public SceneItem
{
public:

    Operator(TYPE t, int x, int y, QGraphicsItem* parent=nullptr);
    Operator(const int id, TYPE t, int x, int y, QGraphicsItem* parent=nullptr);

    virtual void execute();
protected:

};

#endif // OPERATORS_H
