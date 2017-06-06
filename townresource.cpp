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
    return lrint(getBulkValue(getStock() - num, num));
}

int TownResource::inPrice(int num) const
{
    return lrint(getBulkValue(getStock(), num));
}

float TownResource::getBulkValue(int startStock, int deltaStock) const
{
    float decay = getResource()->getDecay();
    return getResource()->getValue() * exp2(decay * startStock) * (1 - exp2(deltaStock * decay)) / (1 - exp2(decay));
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

float TownResource::getStockAsFloat()
{
    return m_stock;
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
