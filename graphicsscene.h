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
    GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    void setCurrent(SceneItem::TYPE t);
    void setDrawing(bool d);
    void setErasing(bool e);
    void loadAxes(bool load);
    void clear();
    void createUndoStack();
    QAction *getUndoAction() { return m_undoAction; }
    QAction *getRedoAction() { return m_redoAction; }
    QGraphicsItem* Center() const { return m_Center; }

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

    bool drawing = false;
    bool erasing = false;
    SceneItem::TYPE type;
    QGraphicsItem* m_AxisX = nullptr;
    QGraphicsItem* m_AxisY = nullptr;
    QAction *m_undoAction = nullptr;
    QAction *m_redoAction = nullptr;
    QUndoStack *m_undoStack = nullptr;
    QGraphicsItem* m_Center = nullptr;
};

#endif // GRAPHICSSCENE_H
