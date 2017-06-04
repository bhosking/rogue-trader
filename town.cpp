#include "town.h"
Town::Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name, QPointF pos)
    :m_population(population), m_name(name), m_pos(pos)
{
    for (std::tuple<const Resource *, float, float> resourceInits:resourceRatesStock)
    {
        m_resources.push_back(new TownResource(std::get<0>(resourceInits), std::get<1>(resourceInits), std::get<2>(resourceInits)));
    }
    for (TownResource * townResource : getResources())
    {
        townResource->setTownResourcesNeeded(getResources());
    }
}

const std::vector<TownResource *> &Town::getResources() const
{
    return m_resources;
}

unsigned Town::getPopulation() const
{
   return m_population;
}

const std::string &Town::getName() const
{
    return m_name;
}

QPointF Town::getPos() const
{
    return m_pos;
}

void Town::processTick(World *)
{

}
