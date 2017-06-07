#ifndef TRADER_H
#define TRADER_H
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
    const Town *getDestinationTown();
    void setDestinationTown(const Town *destination);
    const std::unordered_map<const Resource *, int> &getInventory() const;
    void setInventory(const std::unordered_map<const Resource *, int> other);
    int getInventoryResource(const Resource *resource) const;
    void setInventoryResource(const Resource *resource, int value);
    void adjustInventory(const std::unordered_map<const Resource *, int> changes);
    void adjustInventoryResource(const Resource *resource, int change);
    void processTick(World &);

private:
    float m_speed;
    bool m_atDestination;
    const Town * m_destination;
    std::unordered_map<const Resource *, int> m_inventory;
};

#endif // TRADER_H
