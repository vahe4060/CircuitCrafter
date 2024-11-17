#include "graphicsview.h"
#include "qevent.h"


GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() == Qt::MiddleButton)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        translate(event->pos().x(),event->pos().y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // zoom
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        } else {
            factor = 0.90909;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);
    }
    else {
    QGraphicsView::wheelEvent(event);
    }
}
