#include <sstream>
#include "info.h"
#include "town.h"
#include "townresource.h"
#include "resource.h"
#include "world.h"

Info::Info(const Town *town, int tick)
    :m_town(town), m_tick(tick)
{
    m_population = town->getPopulation();
    for (const TownResource * townResource : town->getResources())
    {
        m_resources.push_back(std::pair<const Resource *, int> (townResource->getResource(), townResource->getStock()));
    }
}

const std::vector<std::pair<const Resource *, int> > &Info::getResources() const
{
    return m_resources;
}

int Info::getTick() const
{
    return m_tick;
}

const Town *Info::getTown() const
{
    return m_town;
}

Info &Info::operator=(const Info &other)
{
   m_town = other.getTown();
   m_tick = other.getTick();
   m_resources = other.getResources();
   m_population = other.getPopulation();
   return *this;
}

bool Info::isOlderThan(const Info &other) const
{
    return getTick() > other.getTick();
}

std::string Info::getTownNameStockAndMedianPricesAsString() const
{
    std::stringstream ss;
    ss << m_town->getName() << " (" << getPopulation() << ")" << "\n";
    for(std::pair<const Resource *,int> resourceStockPair: getResources())
    {
        ss << resourceStockPair.first->getName() << "(" <<resourceStockPair.second << ") "
           << (resourceStockPair.first->inPrice(resourceStockPair.second, getPopulation())
               +resourceStockPair.first->outPrice(resourceStockPair.second, getPopulation()))/2 <<"g\n";
    }
    std::string infoAge = getAgeOfInfoAsString();
    if(infoAge=="")
    {
        ss << "(current)";
    }
    else
    {
        ss <<"("<< infoAge << " old)";
    }

    return ss.str();
}

int Info::getAgeOfInfo() const
{
    return World::getWorld().getTick()- getTick();
}

int Info::getPopulation() const
{
    return m_population;
}

std::string Info::getAgeOfInfoAsString() const
{
    return World::ticksToTime(getAgeOfInfo());
}
