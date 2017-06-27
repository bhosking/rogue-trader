#ifndef TRADER_H
#define TRADER_H
#include <string>
#include <QPointF>
#include <unordered_map>
#include <memory>
#include "updatableentity.h"

class Town;
class Resource;
class Info;

class Trader : public UpdatableEntity
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

    const std::unordered_map<Town *, std::shared_ptr<const Info> > &getAllHeldInfo() const;
    /**
     * @brief getHeldInfoOnTown
     * Checks to see if there is information on the town and if so return it
     * @param town A pointer to a town object
     * @return A shared pointer to information on the town.
     * If this information holder has no information on the town the null shared_ptr is returned instead.
     */
    std::shared_ptr<const Info> getHeldInfoOnTown(Town * town) const;

    void addInfo(const std::shared_ptr<const Info> &newInfo);
    std::shared_ptr<const Info> addTownCurrentInfo(Town *town);
private:
    float m_speed;
    bool m_atDestination;
    Town * m_destination;
    std::unordered_map<const Resource *, int> m_inventory;
    int m_gp;
    float m_foodPerDistance;
    float m_energy;
    std::unordered_map<Town *, std::shared_ptr<const Info> > m_info;
};

#endif // TRADER_H
