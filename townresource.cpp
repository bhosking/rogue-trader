#include <math.h>
#include <algorithm>
#include "townresource.h"
#include "resource.h"

TownResource::TownResource(const Resource *resource, float rate, int stock)
    :m_resource(resource), m_rate(rate), m_stock((float)stock)
{

}

const Resource *TownResource::getResource() const
{
    return m_resource;
}

float TownResource::getRate() const
{
    return m_rate;
}

int TownResource::getStock() const
{
    return (int)m_stock;
}

int TownResource::outPrice(int num) const
{
    return getResource()->outPrice(getStock(),num);
}

int TownResource::inPrice(int num) const
{
    return getResource()->inPrice(getStock(),num);
}
float TownResource::getCurrentRate() const
{
    float currentRate = getRate();
    for (std::pair<TownResource *, float> neededResource : getTownResourcesNeeded())
    {
        currentRate = std::min(neededResource.first->getStockAsFloat() / neededResource.second, currentRate);
    }
    return currentRate;
}

void TownResource::produceResource()
{
    float currentRate = getCurrentRate();
    // Reduce all required stock levels
    for (std::pair<TownResource *, float> neededResource : getTownResourcesNeeded())
    {
        neededResource.first->adjustStock(-1 * currentRate * neededResource.second);
    }
    adjustStock(currentRate);
}

int TownResource::consumeResources(int currentPopulation)
{
        float consumed = currentPopulation * getResource()->getConsume();
        float stock = getStockAsFloat();
        setStock(std::max(stock - consumed, static_cast<float>(0)));
        if (getResource()->getName() == "Food")
        {
            if (stock < consumed)
            {
                return -1;
            }
            else if (stock >= consumed * 1000)
            {
                return 1;
            }
        }
        return 0;
}

float TownResource::getStockAsFloat()
{
    return m_stock;
}

float TownResource::getValue()
{
    return getResource()->getValue() * exp2(getStock() * getResource()->getDecay());
}

const std::vector<std::pair<TownResource *, float> > &TownResource::getTownResourcesNeeded() const
{
    return m_townResourcesNeeded;
}

void TownResource::setStock(int newStock)
{
    m_stock = (float)newStock;
}

void TownResource::setStock(float newStock)
{
    m_stock = newStock;
}

void TownResource::setTownResourcesNeeded(const std::vector<TownResource *> &townResources)
{
    for (std::pair<const Resource *, float> need:getResource()->getNeeds())
    {
        for (TownResource * townResource:townResources) {
            if (townResource->getResource() == need.first) {
                m_townResourcesNeeded.push_back(std::pair<TownResource *, float> (townResource, need.second));
                break;
            }
        }
    }
}

void TownResource::adjustStock(int deltaStock)
{
    setStock(getStockAsFloat() + deltaStock);
}

void TownResource::adjustStock(float deltaStock)
{
    setStock(getStockAsFloat() + deltaStock);
}
