#ifndef TOWN_H
#define TOWN_H
#include <vector>
#include <QPointF>
#include <unordered_map>
#include <memory>
#include "circularsceneitem.h"
#include "updatableentity.h"

class Resource;
class TownResource;
class InformationHolder;

class Town : public CircularSceneItem, public UpdatableEntity
{
public:
    Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, int population, std::string &name);
    TownResource *getResource(const Resource *resource);
    const std::vector<TownResource *> &getResources() const;
    int getPopulation() const;
    const std::string & getName() const;
    int getGP() const;
    void adjustGP(int change);
    void adjustPopulation(int change);
    void processTick(World &);
private:
    std::vector<TownResource *> m_resources;
    int m_population;
    const std::string m_name;
    void setWorkers();
    void consumeResources();
    void produceResources();
    int m_gp;
    InformationHolder *m_info;
};

#endif // TOWN_H
