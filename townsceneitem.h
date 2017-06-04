#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include <QGraphicsItem>
#include "town.h"

class TownSceneItem :public QGraphicsItem, public Town
{
public:
    TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name, QPointF pos);
};

#endif // TOWNSCENEITEM_H
