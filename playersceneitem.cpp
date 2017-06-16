#include "playersceneitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "map.h"
#include "world.h"
#include "townsceneitem.h"

float length(const QPointF &p)
{
    return sqrtf(p.x()*p.x()+p.y()*p.y());
}

QPointF normalized(const QPointF &p)
{
    float len = length(p);
    return QPointF(p.x()/len,p.y()/len);
}

PlayerSceneItem::PlayerSceneItem()
    :m_explorationRadius(20),m_targetVector(0,0)
{
    setBoundingRegionGranularity(0.04);
    setZValue(2);
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
    if(isAtDestination()&&getDestinationTown())
    {
        painter->drawEllipse(QPointF(),m_radius+2,m_radius+2);
    }
    else
    {
        painter->drawEllipse(QPointF(),m_radius,m_radius);
    }
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

    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    const TownSceneItem * townUnderMouse = World::getWorld().getTownSceneItemUnderMouse(event);
    if(townUnderMouse&&townUnderMouse->isVisible())
    {
        m_targetVector = townUnderMouse->getPos()-scenePos();
    }
    else
    {
        m_targetVector = event->pos();
    }

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
    float x = std::min(0.0,m_targetVector.x()) - m_radius - 2;
    float y = std::min(0.0,m_targetVector.y()) - m_radius - 2;
    float width = fabs(m_targetVector.x()) + 2*m_radius + 4;
    float height = fabs(m_targetVector.y()) + 2*m_radius + 4;

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
        emit arrivedAtTown(info,getInventory());
    }
    Player::processTick(world);
    update();
}

void PlayerSceneItem::updateTownInfo()
{
    addTownCurrentInfo(getDestinationTown());
}

void PlayerSceneItem::buy(const Resource *resource, int amount)
{
    Trader::buy(resource,amount);
    std::shared_ptr<const Info> info = addTownCurrentInfo(getDestinationTown());
    emit arrivedAtTown(info,getInventory());
}

void PlayerSceneItem::sell(const Resource *resource, int amount)
{
    Trader::sell(resource,amount);
    std::shared_ptr<const Info> info = addTownCurrentInfo(getDestinationTown());
    emit arrivedAtTown(info,getInventory());
}

void PlayerSceneItem::move()
{
    QPointF movementVector;
    if(length(m_targetVector) < getSpeed())
    {
        setStoppedAtDestination(true);
        movementVector = m_targetVector;
    }
    else
    {
        movementVector = normalized(m_targetVector)*getSpeed();
    }
    moveBy(movementVector.x(),movementVector.y());
    m_targetVector -= movementVector;
}
