#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include "town.h"
#include <QPointF>

class Info;

class TownSceneItem :public Town
{
public:
    TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void playerKnows();
    void processTick(World & world);

private:
    bool m_showPrices;
    bool m_playerKnowledge;
    QRectF pricesRectangle;
    void paintPrices(QPainter *painter, std::shared_ptr<const Info> &info);
    void updatePricesDisplayRectangle(QPainter *painter, std::shared_ptr<const Info> &info);
    mutable std::shared_ptr<const Info> m_currentInfo;
};

#endif // TOWNSCENEITEM_H
