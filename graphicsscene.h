#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QtWidgets>
#include "labels.h"
#include "operators.h"

class GraphicsScene: public QGraphicsScene
{
public:
    GraphicsScene(QObject *parent = nullptr);
    GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
    GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    void setCurrent(SceneItem::TYPE t);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool drawing = false;
    SceneItem::TYPE type;
};

#endif // GRAPHICSSCENE_H
