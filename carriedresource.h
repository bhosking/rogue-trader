#ifndef CARRIEDRESOURCE_H
#define CARRIEDRESOURCE_H

class Resource;

class CarriedResource
{
public:
    CarriedResource(Resource const * resource);
    void addAmount(int amountToAdd);
    void removeAmount(int amountToRemove);
    int getAmount();
    void setAmount(int newAmount);
    float getMass();
    float getVolume();
    const Resource * getResource();
private:
    int m_amount;
    const Resource * m_resource;
};

#endif // CARRIEDRESOURCE_H
