#include "graphicsscene.h"
#include "mainwindow.h"

QGraphicsEllipseItem GraphicsScene::central_item = QGraphicsEllipseItem(0,0,1,1, nullptr);

QGraphicsItem *GraphicsScene::centralItem()
{
    return &central_item;
}

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
    addItem(&GraphicsScene::central_item);
    createUndoStack();
}

GraphicsScene::GraphicsScene(const QRectF &sceneRect, QObject *parent): QGraphicsScene(sceneRect, parent)
{
    addItem(&GraphicsScene::central_item);
    createUndoStack();
}

void GraphicsScene::createUndoStack()
{
    m_undoStack = new QUndoStack(this);
    m_undoAction = m_undoStack->createUndoAction(this, tr("&Undo"));
    m_undoAction->setIcon(QIcon(":/Tools/src/Undo.png"));
    m_undoAction->setShortcuts(QKeySequence::Undo);
    m_redoAction = m_undoStack->createRedoAction(this, tr("&Redo"));
    m_redoAction->setIcon(QIcon(":/Tools/src/Redo.png"));
    m_redoAction->setShortcuts(QKeySequence::Redo);
    connect(this, &GraphicsScene::itemMoved, this, &GraphicsScene::onItemMove);
    connect(this, &GraphicsScene::itemCreated, this, &GraphicsScene::onItemNew);
    connect(this, &GraphicsScene::itemErased, this, &GraphicsScene::onItemErase);
}

void GraphicsScene::onItemMove(SceneItem *it, const QPointF &newPos)
{
    m_undoStack->push(new MoveItemCommand(it, newPos));
}

void GraphicsScene::onItemNew(SceneItem::TYPE t, const QPointF &pos)
{
    m_undoStack->push(new NewItemCommand(t, pos));
}

void GraphicsScene::onItemErase(SceneItem *it)
{
    m_undoStack->push(new EraseItemCommand(it));
}

void GraphicsScene::loadAxes(bool show)
{
    if(show)
    {
        if(!m_AxisX)
            m_AxisX = addLine(2500,0,-2500,0, QPen(Qt::PenStyle::DotLine));
        if(!m_AxisY)
            m_AxisY = addLine(0,2500,0,-2500, QPen(Qt::PenStyle::DotLine));
    }
    else
    {
        if(m_AxisY)
            delete m_AxisY;
        if(m_AxisX)
            delete m_AxisX;
        m_AxisX = nullptr;
        m_AxisY = nullptr;
    }
}

void GraphicsScene::setCurrent(SceneItem::TYPE t)
{
    type = t;
    setDrawing(true);
    setErasing(false);
}

void GraphicsScene::setDrawing(bool d)
{
    drawing = d;
}

void GraphicsScene::setErasing(bool e)
{
    erasing = e;
}

void GraphicsScene::clear()
{
    // firstly delete Edges, then the operators/labels
    for(QGraphicsItem* it: GraphicsScene::centralItem()->childItems())
    {
        if(it->type() == Edge::TYPE::EDGE)
            delete it;
    }
    for(QGraphicsItem* it: GraphicsScene::centralItem()->childItems())
    {
        delete it;
    }
}

void GraphicsScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() ==  Qt::Key_Escape)
    {
        setDrawing(false);
        setErasing(false);
        MainWindow::instance()->View()->setCursor(QCursor());
    }
    if(event->key() == Qt::Key_Delete && m_activeItem)
    {
        emit itemErased(static_cast<SceneItem*>(m_activeItem->parentItem()));
        m_activeItem = nullptr;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(drawing)
        emit itemCreated(type, event->scenePos());
    else
        m_activeItem = itemAt(event->scenePos(), QTransform());
    QGraphicsScene::mousePressEvent((event));
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // if (m_activeItem)
        // emit itemMoved(static_cast<SceneItem *>(m_activeItem->parentItem()), event->scenePos());
    QGraphicsScene::mouseReleaseEvent(event);
}
