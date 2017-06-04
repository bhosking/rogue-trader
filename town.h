#ifndef TOWN_H
#define TOWN_H
#include <qvector2d.h>
#include "updatableentity.h"
#include "unordered_map"
#include "townresource.h"

class Town : public UpdatableEntity
{
public:
    Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name, QPointF pos);
    const std::vector<TownResource *> &getResources() const;
    unsigned getPopulation() const;
    const std::string & getName() const;
    QPointF getPos() const;
    void processTick(World *);
private:
    std::vector<TownResource *> m_resources;
    const unsigned m_population;
    const std::string m_name;
    const QPointF m_pos;
};

#endif // TOWN_H
