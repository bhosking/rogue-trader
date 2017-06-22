#ifndef TRADER_H
#define TRADER_H
#include <string>
#include <QPointF>
#include <unordered_map>
#include "updatableentity.h"
#include "informationholder.h"

class Town;
class Resource;

class Trader : public UpdatableEntity, public InformationHolder
{
public:
    Trader();
    virtual QPointF getPos() const = 0;
    float getSpeed() const;
    void setSpeed(float);
    bool isAtDestination() const;
    void setStoppedAtDestination(bool);
    Town *getDestinationTown();
    void setDestinationTown(Town *destination);
    const std::unordered_map<const Resource *, int> &getInventory() const;
    void setInventory(const std::unordered_map<const Resource *, int> other);
    int getInventoryResource(const Resource *resource) const;
    void setInventoryResource(const Resource *resource, int value);
    void adjustInventory(const std::unordered_map<const Resource *, int> changes);
    void adjustInventoryResource(const Resource *resource, int change);
    int getGP() const;
    void setGP(int gp);
    void adjustGP(int change);
    virtual void buy(const Resource *resource, int amount);
    virtual void sell(const Resource *resource, int amount);
    void processTick(World &);
    std::string outPutInventoryAsString();

private:
    float m_speed;
    bool m_atDestination;
    Town * m_destination;
    std::unordered_map<const Resource *, int> m_inventory;
    int m_gp;
    float m_foodPerDistance;
    float m_energy;
};

#endif // TRADER_H
