#include "graphicsview.h"
#include "qevent.h"
#include "mainwindow.h"
#include "graphicsscene.h"


GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_seletion(QRubberBand(QRubberBand::Rectangle, this))
{
    m_seletion.hide();
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() == Qt::MiddleButton)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        translate(event->pos().x(),event->pos().y());
    }
    else if(!m_seletion.isHidden())
        m_seletion.setGeometry(QRect(m_seletion_origin, event->pos()).normalized());
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
    else
        QGraphicsView::wheelEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    clearHighlight();
    if (event->button() == Qt::RightButton) {
        m_seletion_origin = event->pos();
        m_seletion.setGeometry(QRect(m_seletion_origin, QSize()));
        m_seletion.show();
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_seletion.isHidden()) {
        QRect rubberBandRect = m_seletion.geometry();
        QPointF topLeft = mapToScene(rubberBandRect.topLeft());
        QPointF bottomRight = mapToScene(rubberBandRect.bottomRight());
        QList<QGraphicsItem*> selected = scene()->items(QRectF(topLeft, bottomRight));
        for (QGraphicsItem *it: selected) {
            SceneItem *parentItem = dynamic_cast<SceneItem *>(it->parentItem());
            if (parentItem)
                m_selected_items.insert(parentItem);
        }
        m_seletion.hide();
        highlightSelected();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::highlightSelected(const QPen &pen)
{
    for (SceneItem *it: m_selected_items) {
        it->setSelected(true);
        it->highlight(pen);
    }
}

void GraphicsView::clearHighlight()
{
    QPen pen(QBrush(Qt::GlobalColor(MainWindow::WireColor())), 2);
    for (SceneItem *it: m_selected_items) {
        it->setSelected(false);
        it->highlight(pen);
    }
    m_seletion.resize(0, 0);
    m_selected_items.clear();
}

void GraphicsView::eraseSelected()
{
    for (SceneItem *it: m_selected_items) {
        emit static_cast<GraphicsScene *>(scene())->itemErased(it);
    }
    m_selected_items.clear();
    m_seletion.resize(0, 0);
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Escape:
            clearHighlight(); break;
        case Qt::Key_Delete:
            eraseSelected(); break;
        default:
            break;
    }
    QGraphicsView::keyPressEvent(event);
}
