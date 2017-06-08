#include <sstream>
#include "town.h"
#include "townresource.h"
#include "resource.h"

Town::Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, unsigned population, std::string &name)
    :m_population(population), m_name(name)
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

TownResource *Town::getResource(const Resource *resource)
{
    for (TownResource * townResource : getResources())
    {
        if (townResource->getResource() == resource)
        {
            return townResource;
        }
    }
    return nullptr;
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

void Town::processTick(World &)
{
    produceResources();
}

void Town::produceResources()
{
    for (TownResource * townResource : getResources())
    {
        townResource->produceResource();
    }
}
