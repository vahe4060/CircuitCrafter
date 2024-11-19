#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QtWidgets>
#include "labels.h"
#include "operators.h"
#include <QGraphicsScene>
#include <QObject>

class GraphicsScene: public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = nullptr);
    GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);

    void setCurrent(SceneItem::TYPE t);
    void setDrawing(bool d);
    void setErasing(bool e);
    void loadAxes(bool load);
    void clear();
    void createUndoStack();
    QAction *getUndoAction() { return m_undoAction; }
    QAction *getRedoAction() { return m_redoAction; }
    static QGraphicsItem *centralItem();

signals:
    void itemMoved(SceneItem *it, const QPointF &newPos);
    void itemCreated(SceneItem::TYPE t, const QPointF &pos);
    void itemErased(SceneItem *it);

public slots:
    void onItemMove(SceneItem *it, const QPointF &newPos);
    void onItemNew(SceneItem::TYPE t, const QPointF &pos);
    void onItemErase(SceneItem *it);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QPointF m_origin;
    bool drawing = false;
    SceneItem::TYPE type;
    QGraphicsItem* m_AxisX = nullptr;
    QGraphicsItem* m_AxisY = nullptr;
    QAction *m_undoAction = nullptr;
    QAction *m_redoAction = nullptr;
    QUndoStack *m_undoStack = nullptr;
    QGraphicsItem *m_activeItem = nullptr;

    static QGraphicsEllipseItem central_item;
};

#endif // GRAPHICSSCENE_H
