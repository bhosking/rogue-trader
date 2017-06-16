#include <sstream>
#include "trader.h"
#include "town.h"
#include "townresource.h"
#include "resource.h"

Trader::Trader()
    :m_speed(1),m_atDestination(true),m_destination(nullptr),m_gp(0)
{

}

float Trader::getSpeed() const
{
    return m_speed;
}

void Trader::setSpeed(float newSpeed)
{
    m_speed = newSpeed;
}

bool Trader::isAtDestination() const
{
    return m_atDestination;
}

void Trader::setStoppedAtDestination(bool stopped)
{
    m_atDestination = stopped;
}

Town *Trader::getDestinationTown()
{
    return m_destination;
}

void Trader::setDestinationTown(Town * destination)
{
    m_destination = destination;
}

const std::unordered_map<const Resource *, int> &Trader::getInventory() const
{
    return m_inventory;
}

void Trader::setInventory(const std::unordered_map<const Resource *, int> other)
{
    m_inventory = other;
}

int Trader::getInventoryResource(const Resource *resource) const
{
    std::unordered_map<const Resource *, int>::const_iterator got = getInventory().find(resource);
    if (got == getInventory().end())
    {
        return 0;
    }
    else
    {
        return got->second;
    }
}

void Trader::adjustInventoryResource(const Resource *resource, int change)
{
    setInventoryResource(resource, getInventoryResource(resource) + change);
}

int Trader::getGP() const
{
    return m_gp;
}

void Trader::setGP(int gp)
{
    m_gp = gp;
}

void Trader::adjustGP(int change)
{
    setGP(getGP() + change);
}

void Trader::buy(const Resource *resource, int amount)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown)
    {
        TownResource *townResource = destinationTown->getResource(resource);
        int inStock = townResource->getStock();
        int population = destinationTown->getPopulation();
        int buyAmount = std::min(resource->howMuchCanIBuy(inStock, population, getGP()), amount);
        if(buyAmount==0)
            return;
        adjustGP(-1 * resource->outPrice(inStock, population, buyAmount));
        townResource->adjustStock(-1 * buyAmount);
        addTownCurrentInfo(destinationTown);
        adjustInventoryResource(resource, buyAmount);

    }
}

void Trader::sell(const Resource *resource, int amount)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown)
    {
        TownResource *townResource = destinationTown->getResource(resource);
        adjustInventoryResource(resource, -1 * amount);
        adjustGP(resource->inPrice(townResource->getStock(), destinationTown->getPopulation(), amount));
        townResource->adjustStock(amount);
        addTownCurrentInfo(destinationTown);
    }
}

void Trader::setInventoryResource(const Resource *resource, int value)
{
    if(value==0)
    {
        auto resourceLocation = m_inventory.find(resource);
        if(resourceLocation!=m_inventory.end())
        {
            m_inventory.erase(resourceLocation);
        }
    }
    else
    {
        m_inventory[resource] = value;
    }
}

void Trader::adjustInventory(const std::unordered_map<const Resource *, int> changes)
{
    for (std::pair<const Resource *, int> resourceChange : changes)
    {
        adjustInventoryResource(resourceChange.first, resourceChange.second);
    }
}

void Trader::processTick(World &)
{

}

std::string Trader::outPutInventoryAsString()
{
    std::stringstream ss;
    ss <<getGP() << "gp\n";
     for(std::pair<const Resource *,int> resourceStockPair: getInventory())
    {
        ss << resourceStockPair.first->getName() << "(" <<resourceStockPair.second << ")\n";
    }
    return ss.str();
}
