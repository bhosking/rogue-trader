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
    Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, int population, std::string &name);
    TownResource *getResource(const Resource *resource);
    const std::vector<TownResource *> &getResources() const;
    int getPopulation() const;
    const std::string & getName() const;
    virtual QPointF getPos() const = 0;
    void adjustPopulation(int change);
    void processTick(World &);
private:
    std::vector<TownResource *> m_resources;
    int m_population;
    const std::string m_name;
    void setWorkers();
    void consumeResources();
    void produceResources();
};

#endif // TOWN_H
