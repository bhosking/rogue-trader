#ifndef TOWNRESOURCE_H
#define TOWNRESOURCE_H
#include "resource.h"

class TownResource
{
public:
    TownResource(const Resource * resource, float rate, float stock = 0);
    const Resource * getResource() const;
    float getRate() const;
    float getStock() const;
    float outPrice(int num = 1) const;
    float inPrice(int num = 1) const;  
    const std::vector<std::pair<TownResource *,float> > & getTownResourcesNeeded() const;
    void setStock(float newStock);
    void setTownResourcesNeeded(std::vector<TownResource *> &neededResources);

private:
    float getBulkValue(int startStock, int deltaStock = 1) const;
    const Resource * m_resource;
    float m_rate;
    float m_stock;
    std::vector<std::pair<TownResource *,float> > m_townResourcesNeeded;
};

#endif // TOWNRESOURCE_H
