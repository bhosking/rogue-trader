#include "townsceneitem.h"
#include <QPainter>
#include <QBrush>
#include <QRadialGradient>
TownSceneItem::TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name)
    :Town(resourceRatesStock,population,name)
{

}

void TownSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkRed,2));
    painter->setBrush(QBrush(QRadialGradient(QPointF(),m_radius)));
    painter->drawEllipse(QPointF(),m_radius,m_radius);
}

const QPointF &TownSceneItem::getPosition() const
{
    return scenePos();
}
