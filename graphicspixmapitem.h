#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H
#include <QtWidgets>
#include <QGraphicsPixmapItem>

class GraphicsPixmapItem: public QGraphicsPixmapItem
{
public:
    explicit GraphicsPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    QPointF m_mousePos;
};

#endif // GRAPHICSPIXMAPITEM_H
