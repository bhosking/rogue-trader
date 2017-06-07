#ifndef TOWN_H
#define TOWN_H
#include <vector>
#include <QPointF>
#include <unordered_map>
#include <memory>
#include "updatableentity.h"
#include "informationholder.h"

class Resource;
class TownResource;
class Info;

class Town : public UpdatableEntity, public InformationHolder
{
public:
    Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name);
    const std::vector<TownResource *> &getResources() const;
    unsigned getPopulation() const;
    const std::string & getName() const;
    virtual QPointF getPos() const = 0;
    void processTick(World &);
private:
    std::vector<TownResource *> m_resources;
    const unsigned m_population;
    const std::string m_name;
    void produceResources();
};

#endif // TOWN_H
