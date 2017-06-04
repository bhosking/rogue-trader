#include "townsceneitem.h"
#include <QPainter>
#include <QBrush>
#include <QRadialGradient>
TownSceneItem::TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name)
    :Town(resourceRatesStock,population,name),m_showPrices(false)
{
    setAcceptHoverEvents(true);
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
    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkRed,2));
    painter->setBrush(QBrush(QRadialGradient(QPointF(),m_radius)));
    painter->drawEllipse(QPointF(),m_radius,m_radius);
    if(m_showPrices)
    {
        paintPrices(painter);
    }
}

void TownSceneItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_showPrices = true;
    prepareGeometryChange();
    update();
}

void TownSceneItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_showPrices = false;
    prepareGeometryChange();
    update();
}

const QPointF &TownSceneItem::getPosition() const
{
    return scenePos();
}

void TownSceneItem::processTick(World *)
{

}

void TownSceneItem::paintPrices(QPainter *painter)
{
    painter->setPen(QPen(Qt::black,2));
    updatePricesDisplayRectangle(painter);
    painter->drawRoundedRect(pricesRectangle,5,5);
    painter->drawText(pricesRectangle.adjusted(5,5,-5,-5),QString(getStockAndMedianPricesAsString().c_str()));
}

QRectF TownSceneItem::updatePricesDisplayRectangle(QPainter *painter)
{
    pricesRectangle = painter->boundingRect(QRect(),Qt::AlignLeft,QString(getStockAndMedianPricesAsString().c_str()));
    pricesRectangle.moveTopLeft(QPointF(-pricesRectangle.width()/2,-pricesRectangle.height() - m_radius - 5));
    pricesRectangle.adjust(-5.0,-5.0,5.0,5.0);
    prepareGeometryChange();
    update();
    return pricesRectangle;
}
