#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include "circularsceneitem.h"
#include "town.h"
#include <QPointF>

class TownSceneItem :public CircularSceneItem, public Town
{
public:
    TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    const QPointF &getPosition() const;
    void processTick(World * world);

private:
    bool m_showPrices;
    QRectF pricesRectangle;
    void paintPrices(QPainter *painter);
    QRectF updatePricesDisplayRectangle(QPainter *painter);
};

#endif // TOWNSCENEITEM_H
