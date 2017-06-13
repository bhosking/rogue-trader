#include <sstream>
#include <algorithm>
#include "town.h"
#include "townresource.h"
#include "resource.h"

Town::Town(std::vector<std::tuple<const Resource *, float, float> > &resourceRatesStock, int population, std::string &name)
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

int Town::getPopulation() const
{
   return m_population;
}

const std::string &Town::getName() const
{
    return m_name;
}

void Town::adjustPopulation(int change)
{
    m_population = std::max(m_population + change, 0);
}

void Town::processTick(World &)
{
    setWorkers();
    produceResources();
    consumeResources();
}

void Town::setWorkers()
{
    //Placeholder logic distributes evenly
    int numResources = getResources().size();
    float workersEach = static_cast<float>(getPopulation()) / numResources;
    for (TownResource * townResource : getResources())
    {
        townResource->setWorkers(workersEach);
    }
}

void Town::consumeResources()
{
    int population = getPopulation();
    for (TownResource * townResource : getResources())
    {
        int deltaPopulation = townResource->consumeResources(population);
        if (deltaPopulation != 0)
        {
            adjustPopulation(deltaPopulation);
        }
    }
}

void Town::produceResources()
{
    for (TownResource * townResource : getResources())
    {
        townResource->produceResource();
    }
}
