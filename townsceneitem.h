#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include "circularsceneitem.h"
#include "town.h"

class TownSceneItem :public CircularSceneItem, public Town
{
public:
    TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name, QPointF pos);
};

#endif // TOWNSCENEITEM_H
