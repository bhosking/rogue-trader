#include "townsceneitem.h"
TownSceneItem::TownSceneItem(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name, QPointF pos)
    :Town(resourceRatesStock,population,name,pos)
{

}
