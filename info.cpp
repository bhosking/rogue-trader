#include <sstream>
#include "info.h"
#include "town.h"
#include "townresource.h"
#include "resource.h"
#include "world.h"

Info::Info(Town *town, int tick)
    :m_town(town), m_tick(tick)
{
    m_population = town->getPopulation();
    m_gp = town->getGP();
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

Town *Info::getTown() const
{
    return m_town;
}

Info &Info::operator=(const Info &other)
{
   m_town = other.getTown();
   m_tick = other.getTick();
   m_resources = other.getResources();
   m_gp = other.getGP();
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
    ss << m_town->getName() << " (" << getPopulation() << ") " << getGP() << "g\n";
    for(std::pair<const Resource *,int> resourceStockPair: getResources())
    {
        ss << resourceStockPair.first->getName() << " (" <<resourceStockPair.second << ") "
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

int Info::getGP() const
{
    return m_gp;
}

int Info::getValue() const
{
    return 50 + 50 * 1440 / (getAgeOfInfo() + 1440);
}

int Info::getProfit(const Info &oldInfo, const Info &tradeInfo) const
{
    int oldGP = oldInfo.getGP();
    int newGP = getGP();
    int tradeGP = tradeInfo.getGP();
    std::vector<std::pair<const Resource *, int> > oldShoppingList = tradeInfo.getShoppingList(oldInfo, oldGP);
    std::vector<std::pair<const Resource *, int> > oldShoppingListRev = oldInfo.getShoppingList(tradeInfo, tradeGP);
    std::vector<std::pair<const Resource *, int> > newShoppingList = tradeInfo.getShoppingList(*this, newGP);
    std::vector<std::pair<const Resource *, int> > newShoppingListRev = getShoppingList(tradeInfo, tradeGP);
}

std::vector<std::pair<const Resource *, int> > &Info::getShoppingList(const Info &otherInfo, int gp) const
{
    int pop = getPopulation();
    int otherPop = otherInfo.getPopulation();
    std::vector<std::pair<float, const Resource *> > profitResources;
    std::vector<std::pair<const Resource *, int> > otherResources = otherInfo.getResources();
    std::vector<std::pair<const Resource *, int> > resources = getResources();
    for (std::vector<int>::size_type i = 0; i != resources.size(); i++)
    {
        std::pair<const Resource *, int> stockResource = resources[i];
        const Resource *resource = stockResource.first;
        int stock = stockResource.second;
        float profit = resource->getRelativeDifference(otherResources[i].second, otherPop, stock, pop);
        if (profit > 0)
        {
            profitResources.push_back(std::pair<float, const Resource *>(profit, resource));
        }
    }
    std::sort(profitResources.begin(),profitResources.end());
}

std::string Info::getAgeOfInfoAsString() const
{
    return World::ticksToTime(getAgeOfInfo());
}
