#include "playersceneitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QVector2D>
#include "world.h"
PlayerSceneItem::PlayerSceneItem()
{
}

void PlayerSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkGreen,2));
    painter->drawEllipse(QPointF(),m_radius,m_radius);
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
    float x = std::min(0.0,m_targetVector.x()) - m_radius;
    float y = std::min(0.0,m_targetVector.y()) - m_radius;
    float width = fabs(m_targetVector.x()) + 2*m_radius;
    float height = fabs(m_targetVector.y()) + 2*m_radius;

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
        world->getMap()->explore(scenePos(),20);
    }
    Player::processTick(world);
    update();
}

void PlayerSceneItem::updateMovementDirection()
{
    m_movementDirection = QVector2D(m_targetVector).normalized().toPointF();
}
