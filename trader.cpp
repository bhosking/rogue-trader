#include "trader.h"

Trader::Trader()
    :m_speed(1),m_atDestination(true),m_destination(nullptr)
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

void Trader::setInventoryResource(const Resource *resource, int value)
{
    m_inventory[resource] = value;
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
