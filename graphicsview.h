#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "qevent.h"
#include "qgraphicsitem.h"
#include <QGraphicsView>
#include <graphicssceneitem.h>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    void eraseSelected();
    void highlightSelected(const QPen &pen = QPen(QBrush(Qt::green), 3));
    void clearHighlight();
    QRubberBand m_seletion;
    QPoint m_seletion_origin;
    QSet<SceneItem *> m_selected_items;
};

#endif // GRAPHICSVIEW_H
