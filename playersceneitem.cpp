#include "playersceneitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <QVector2D>
#include "map.h"
#include "world.h"
#include "townsceneitem.h"
PlayerSceneItem::PlayerSceneItem()
    :m_explorationRadius(20),m_movementDirection(0,0),m_targetVector(0,0)
{
    setBoundingRegionGranularity(0.04);
}

QPointF PlayerSceneItem::getPos() const
{
    return scenePos();
}

float PlayerSceneItem::getExplorationRadius() const
{
    return m_explorationRadius;
}

void PlayerSceneItem::setExplorationRadius(float newRadius)
{
    m_explorationRadius = newRadius;
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
    if(!boundingRegion(QTransform()).contains(event->pos().toPoint()))
    {
        event->ignore();
        return;
    }
    const TownSceneItem * townUnderMouse = World::getWorld().getTownSceneItemUnderMouse(event);
    if(townUnderMouse)
    {
        m_targetVector = townUnderMouse->getPos()-scenePos();
    }
    else
    {
        m_targetVector = event->pos();
    }

    updateMovementDirection();
    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    const TownSceneItem * townUnderMouse = World::getWorld().getTownSceneItemUnderMouse(event);
    if(townUnderMouse)
    {
        m_targetVector = townUnderMouse->getPos()-scenePos();
    }
    else
    {
        m_targetVector = event->pos();
    }

    updateMovementDirection();
    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setDestinationTown(World::getWorld().getTownSceneItemUnderMouse(event));
    setStoppedAtDestination(false);
    emit leftTown();
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

void PlayerSceneItem::processTick(World &world)
{
    if(!isAtDestination())
    {    
        move();
        world.getMap()->explore(scenePos(),getExplorationRadius());
    }
    //if at destination and its a town, add its information.
    else if(getDestinationTown())
    {
        std::shared_ptr<const Info> info = addTownCurrentInfo(getDestinationTown());
        emit arrivedAtTown(info);
    }
    Player::processTick(world);
    update();
}

void PlayerSceneItem::move()
{
    QPointF movementVector;
    if(QVector2D(m_targetVector).length() < getSpeed())
    {
        setStoppedAtDestination(true);
        movementVector = m_targetVector;
    }
    else
    {
        movementVector = m_movementDirection*getSpeed();
    }
    moveBy(movementVector.x(),movementVector.y());
    m_targetVector -= movementVector;
}

void PlayerSceneItem::updateMovementDirection()
{
    m_movementDirection = QVector2D(m_targetVector).normalized().toPointF();
}
