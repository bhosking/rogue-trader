#include "townresource.h"
#include <math.h>

TownResource::TownResource(const Resource *resource, float rate, float stock)
    :m_resource(resource), m_rate(rate), m_stock(stock)
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

float TownResource::getStock() const
{
    return m_stock;
}

float TownResource::outPrice(int num) const
{
    return getBulkValue(getStock() - 1, -1 * num);
}

float TownResource::inPrice(int num) const
{
    return getBulkValue(getStock(), num);
}

float TownResource::getBulkValue(int startStock, int deltaStock) const
{
    float decay = -1 * getResource()->getDecay();
    return exp2(decay * startStock) * (1 - exp2(deltaStock * decay)) / (1 - exp2(decay));
}

float TownResource::getCurrentRate() const
{
    float currentRate = getRate();
    for (std::pair<TownResource *, float> neededResource : getTownResourcesNeeded())
    {
        currentRate = std::min(neededResource.first->getStock() / neededResource.second, currentRate);
    }
    return currentRate;
}

void TownResource::produceResource()
{
    float currentRate = getCurrentRate();
    // Reduce all required stock levels
    for (std::pair<TownResource *, float> neededResource : getTownResourcesNeeded())
    {
        neededResource.first->adjustStock(currentRate * neededResource.second);
    }
    adjustStock(currentRate);
}

const std::vector<std::pair<TownResource *, float> > &TownResource::getTownResourcesNeeded() const
{
    return m_townResourcesNeeded;
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

void TownResource::adjustStock(float deltaStock)
{
    setStock(getStock() + deltaStock);
}
