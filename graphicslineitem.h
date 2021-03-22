#ifndef GRAPHICSLINEITEM_H
#define GRAPHICSLINEITEM_H
#include <QtWidgets>
#include <QGraphicsLineItem>

class GraphicsLineItem: public QGraphicsLineItem
{
public:
    enum TYPE{
        HORIZONAL_UPPER = UserType + 20,
        HORIZONAL_LOWER,
        VERTICAL_LEFT,
        VERTICAL_RIGHT
    };
    explicit GraphicsLineItem(TYPE t, QGraphicsItem *parent = nullptr);
    explicit GraphicsLineItem(TYPE t, const QLineF &line, QGraphicsItem *parent = nullptr);

    //void setLine(const QLineF &line);
    virtual int type() const override { return m_t; }
    virtual QRectF boundingRect() const override;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    //virtual void mousePressEvent(QGraphicsSceneMouseEvent * event)   override;
    //virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;
    TYPE m_t;
};

#endif // GRAPHICSLINEITEM_H
