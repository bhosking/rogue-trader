#include "townsceneitem.h"
#include <QPainter>
#include <QBrush>
#include <QRadialGradient>
#include "world.h"
#include "playersceneitem.h"
#include "info.h"
TownSceneItem::TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name)
    :Town(resourceRatesStock,population,name),m_showPrices(false),m_playerKnowledge(false)
{
    setAcceptHoverEvents(true);
    setVisible(false);
}

QRectF TownSceneItem::boundingRect() const
{
    if(m_showPrices)
    {
        return CircularSceneItem::boundingRect().united(pricesRectangle);
    }
    else
    {
        return CircularSceneItem::boundingRect();
    }
}

void TownSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::shared_ptr<const Info> info = World::getWorld().getPlayerSceneItem()->getHeldInfoOnTown(this);

    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkRed,2));
    painter->setBrush(QBrush(QRadialGradient(QPointF(),m_radius)));
    painter->drawEllipse(QPointF(),m_radius,m_radius);

    if(m_showPrices&&info)
    {
        paintPrices(painter,info);
    }
}

void TownSceneItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(World::getWorld().getPlayerSceneItem()->getHeldInfoOnTown(this))
    {
        m_showPrices = true;
        prepareGeometryChange();
        setZValue(1);
        update();
    }
}

void TownSceneItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_showPrices = false;
    prepareGeometryChange();
    update();
}

void TownSceneItem::playerKnows()
{
    m_playerKnowledge = true;
    setVisible(true);
}

QPointF TownSceneItem::getPos() const
{
    return scenePos();
}

void TownSceneItem::processTick(World &world)
{
    if (!m_playerKnowledge)
    {
        PlayerSceneItem *playerSceneItem = world.getPlayerSceneItem();
        if(playerSceneItem->getHeldInfoOnTown(this))
        {
            playerKnows();
        }
        else
        {
            QPointF pos = playerSceneItem->getPos();
            pos -= getPos();
            if (containedInCircleAtOrigin(pos, playerSceneItem->getExplorationRadius() + m_radius))
            {
                playerKnows();
            }
        }
    }
    Town::processTick(world);
}

void TownSceneItem::paintPrices(QPainter *painter, std::shared_ptr<const Info> &info)
{
    painter->setPen(QPen(Qt::black,2));
    updatePricesDisplayRectangle(painter,info);
    painter->drawRoundedRect(pricesRectangle,5,5);
    painter->drawText(pricesRectangle.adjusted(5,5,-5,-5),QString(info->getTownNameStockAndMedianPricesAsString().c_str()));
}

QRectF TownSceneItem::updatePricesDisplayRectangle(QPainter *painter, std::shared_ptr<const Info> &info)
{
    pricesRectangle = painter->boundingRect(QRect(),Qt::AlignLeft,QString(info->getTownNameStockAndMedianPricesAsString().c_str()));
    pricesRectangle.moveTopLeft(QPointF(-pricesRectangle.width()/2,-pricesRectangle.height() - m_radius - 5));
    pricesRectangle.adjust(-5.0,-5.0,5.0,5.0);
    prepareGeometryChange();
    update();
    return pricesRectangle;
}
