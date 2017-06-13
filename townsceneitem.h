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
    void playerKnows();
    QPointF getPos() const;
    void processTick(World & world);

private:
    bool m_showPrices;
    bool m_playerKnowledge;
    QRectF pricesRectangle;
    void paintPrices(QPainter *painter, std::shared_ptr<const Info> &info);
    QRectF updatePricesDisplayRectangle(QPainter *painter, std::shared_ptr<const Info> &info);
};

#endif // TOWNSCENEITEM_H
