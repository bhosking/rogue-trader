#include <sstream>
#include "info.h"
#include "town.h"
#include "townresource.h"
#include "resource.h"

Info::Info(const Town *town, int tick)
    :m_town(town), m_tick(tick)
{
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
   return *this;
}

bool Info::isOlderThan(const Info &other) const
{
    return getTick() > other.getTick();
}

std::string Info::getStockAndMedianPricesAsString() const
{
    std::stringstream ss;
    for(std::pair<const Resource *,int> resourceStockPair: getResources())
    {
        ss << resourceStockPair.first->getName() << "(" <<resourceStockPair.second << ") "
           << (resourceStockPair.first->inPrice(resourceStockPair.second)+resourceStockPair.first->outPrice(resourceStockPair.second))/2 <<"g\n";
    }
    return ss.str();
}
