#include "playersceneitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QVector2D>
#include "world.h"
PlayerSceneItem::PlayerSceneItem()
{
    setPos(0,0);

}

void PlayerSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::darkGreen);
    painter->drawRect(-5,-5,10,10);
    //checks to see if the item is grabbed
    if(scene()&&scene()->mouseGrabberItem()==this)
    {

    }

    painter->drawLine(QPointF(0,0),m_targetVector);
}

void PlayerSceneItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_targetVector = event->pos();
    updateMovementDirection();
    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_targetVector = event->pos();
    updateMovementDirection();
    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_stopped = false;
    prepareGeometryChange();
    update();
}

QRectF PlayerSceneItem::boundingRect() const
{
    float x = std::min(0.0,m_targetVector.x()) - 5;
    float y = std::min(0.0,m_targetVector.y()) - 5;
    float width = fabs(m_targetVector.x()) + 10;
    float height = fabs(m_targetVector.y()) + 10;

    return QRectF(x,y,width,height);
}

void PlayerSceneItem::processTick(World *world)
{
    if(!m_stopped)
    {
        QPointF movementVector;
        if(QVector2D(m_targetVector).length() < m_speed)
        {
            m_stopped = true;
            movementVector = m_targetVector;
        }
        else
        {
            movementVector = m_movementDirection*m_speed;
        }
        moveBy(movementVector.x(),movementVector.y());
        m_targetVector -= movementVector;
        world->getMap()->explore(scenePos(),10);
    }
    Player::processTick(world);
    update();
}

void PlayerSceneItem::updateMovementDirection()
{
    m_movementDirection = QVector2D(m_targetVector).normalized().toPointF();
}
