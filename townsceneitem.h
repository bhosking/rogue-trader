#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include "circularsceneitem.h"
#include "town.h"
#include <QPointF>

class TownSceneItem :public CircularSceneItem, public Town
{
public:
    TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    const QPointF &getPosition() const;
};

#endif // TOWNSCENEITEM_H
