#ifndef TOWNRESOURCE_H
#define TOWNRESOURCE_H

#include <vector>

class Resource;

class TownResource
{
public:
    TownResource(const Resource * resource, float rate, int stock = 0);
    const Resource * getResource() const;
    float getRate() const;
    int getStock() const;
    int outPrice(int num = 1) const;
    int inPrice(int num = 1) const;
    const std::vector<std::pair<TownResource *,float> > & getTownResourcesNeeded() const;
    void setTownResourcesNeeded(const std::vector<TownResource *> &townResources);
    void produceResource();
    void setStock(int newStock);
    void adjustStock(int deltaStock);

private:
    void setStock(float newStock);
    void adjustStock(float deltaStock);
    float getStockAsFloat();
    const Resource * m_resource;
    float m_rate;
    float m_stock;
    std::vector<std::pair<TownResource *,float> > m_townResourcesNeeded;
    float getCurrentRate() const;
};

#endif // TOWNRESOURCE_H
