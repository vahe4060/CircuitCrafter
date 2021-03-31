#ifndef LABEL_H
#define LABEL_H
#include "graphicssceneitem.h"

class Label : public SceneItem
{
public:

    Label(TYPE t, int x, int y, QGraphicsItem* parent=nullptr);
    Label(const int id, TYPE t, int x, int y, QGraphicsItem* parent=nullptr);

    virtual void execute();
};


#endif // LABEL_H
