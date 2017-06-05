#include "town.h"
#include <sstream>
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

const std::unordered_map<std::string, std::shared_ptr<Info *> > &Town::getInfos() const
{
    return m_infos;
}

std::string Town::getStockAndMedianPricesAsString() const
{
    std::stringstream ss;
    for(const TownResource * resource:getResources())
    {
        ss << resource->getResource()->getName() << "(" <<resource->getStock() << ") "
           << (resource->inPrice()+resource->outPrice())/2 <<"g\n";
    }
    return ss.str();
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
