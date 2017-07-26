#include "playersceneitem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "map.h"
#include "world.h"
#include "townsceneitem.h"

PlayerSceneItem::PlayerSceneItem()
    :m_explorationRadius(100)
{
    setBoundingRegionGranularity(0.04);
    setZValue(2.5);
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
    painter->drawLine(QPointF(0,0),getTargetVector());
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
        setTargetVector(townUnderMouse->getPos()-scenePos());
    }
    else
    {
        setTargetVector(event->pos());
    }

    prepareGeometryChange();
    update();
}

void PlayerSceneItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    const TownSceneItem * townUnderMouse = World::getWorld().getTownSceneItemUnderMouse(event);
    if(townUnderMouse&&townUnderMouse->isVisible())
    {
        setTargetVector(townUnderMouse->getPos()-scenePos());
    }
    else
    {
        setTargetVector(event->pos());
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
    float x = std::min(0.0,getTargetVector().x()) - m_radius - 2;
    float y = std::min(0.0,getTargetVector().y()) - m_radius - 2;
    float width = fabs(getTargetVector().x()) + 2*m_radius + 4;
    float height = fabs(getTargetVector().y()) + 2*m_radius + 4;

    return QRectF(x,y,width,height);
}

void PlayerSceneItem::processTick(World &world)
{
    if(!isAtDestination())
    {    
        move(getSpeed());
        world.getMap()->explore(scenePos(),getExplorationRadius());
        world.setFogPosition(pos());
    }
    Trader::processTick(world);
    update();
}

void PlayerSceneItem::updateTownInfo()
{
    addTownCurrentInfo(getDestinationTown());
}

int PlayerSceneItem::buy(const Resource *resource, int amount)
{
    int buyAmount = Trader::buy(resource,amount);
    emit arrivedAtTown(getHeldInfoOnTown(getDestinationTown()),getInventory());
    return buyAmount;
}

int PlayerSceneItem::sell(const Resource *resource, int amount)
{
    int sellAmount = Trader::sell(resource,amount);
    emit arrivedAtTown(getHeldInfoOnTown(getDestinationTown()),getInventory());
    return sellAmount;
}

void PlayerSceneItem::arrivedAtDestination()
{
    setStoppedAtDestination(true);

    //if at destination and its a town, add its information.
    if(getDestinationTown())
    {
        std::shared_ptr<const Info> info = addTownCurrentInfo(getDestinationTown());
        emit arrivedAtTown(info,getInventory());
    }
}
