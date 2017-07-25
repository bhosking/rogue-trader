#include <sstream>
#include "trader.h"
#include "town.h"
#include "townresource.h"
#include "resource.h"
#include "config.h"
#include "informationholder.h"
#include "info.h"
#include "world.h"

Trader::Trader()
    :m_speed(1),m_atDestination(true),m_destination(nullptr),m_gp(0),m_foodPerDistance(1.0/1024),
      m_energy(0),m_targetVector(0,0), m_info(new InformationHolder)
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
    emit inventoryChanged();
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

int Trader::getGP() const
{
    return m_gp;
}

void Trader::setGP(int gp)
{
    m_gp = gp;
    emit inventoryChanged();
}

void Trader::adjustGP(int change)
{
    setGP(getGP() + change);
}

int Trader::buy(const Resource *resource, int amount)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown)
    {
        TownResource *townResource = destinationTown->getResource(resource);
        int inStock = townResource->getStock();
        int population = destinationTown->getPopulation();
        int buyValue = resource->outPrice(inStock, population, amount);
        if (buyValue > getGP())
        {
            amount = resource->howMuchCanIBuy(inStock, population, getGP());
            if (amount > 0)
            {
                buyValue = resource->outPrice(inStock, population, amount);
            }
        }
        if (amount > 0) {
            adjustGP(-1 * buyValue);
            destinationTown->adjustGP(buyValue);
            townResource->adjustStock(-1 * amount);
            adjustInventoryResource(resource, amount);
        }
        addTownCurrentInfo(destinationTown);
    }
    else
    {
        amount = 0;
    }
    return amount;
}

int Trader::sell(const Resource *resource, int amount)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown)
    {
        TownResource *townResource = destinationTown->getResource(resource);
        int inStock = townResource->getStock();
        int population = destinationTown->getPopulation();
        int sellValue = resource->inPrice(inStock, population, amount);
        if (sellValue > destinationTown->getGP())
        {
            amount = resource->howMuchCanISell(inStock, population, destinationTown->getGP());
            if (amount > 0)
            {
                sellValue = resource->inPrice(inStock, population, amount);
            }
        }
        if (amount > 0) {
            adjustInventoryResource(resource, -1 * amount);
            adjustGP(sellValue);
            townResource->adjustStock(amount);
            destinationTown->adjustGP(-1 * sellValue);
        }
        addTownCurrentInfo(destinationTown);
    }
    else
    {
        amount = 0;
    }
    return amount;
}

void Trader::buyInfo(Town *infoTown)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown && destinationTown != infoTown)
    {
        std::shared_ptr<const Info> theirInfo = destinationTown->getHeldInfoOnTown(infoTown);
        if (theirInfo) {
        int buyValue = theirInfo->getValue();
        if (buyValue > 0 && buyValue <= getGP()) {
            adjustGP(-1 * buyValue);
            addInfo(theirInfo);
            destinationTown->adjustGP(buyValue);
        }
        }
        addTownCurrentInfo(destinationTown);
    }
}

void Trader::sellInfo(Town *infoTown)
{
    Town *destinationTown = getDestinationTown();
    if (isAtDestination() && destinationTown && destinationTown != infoTown)
    {
        std::shared_ptr<const Info> myInfo = getHeldInfoOnTown(infoTown);
        if (myInfo) {
            int sellValue = myInfo->getValue();
            std::shared_ptr<const Info> theirInfo = destinationTown->getHeldInfoOnTown(infoTown);
            if (theirInfo) {
                 sellValue -= theirInfo->getValue();
            }
        if (sellValue > 0 && sellValue <= destinationTown->getGP()) {
            destinationTown->addInfo(myInfo);
            destinationTown->adjustGP(-1 * sellValue);
            adjustGP(sellValue);
        }
        }
        addTownCurrentInfo(destinationTown);
    }
}

void Trader::setInventoryResource(const Resource *resource, int value)
{
    if(value==0)
    {
        auto resourceLocation = m_inventory.find(resource);
        if(resourceLocation!=m_inventory.end())
        {
            m_inventory.erase(resourceLocation);
        }
    }
    else
    {
        m_inventory[resource] = value;
    }
    emit inventoryChanged();
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
    if (!isAtDestination())
    {
        m_energy -= m_foodPerDistance * m_speed;
        if (m_energy <= 0)
        {
            const Resource *foodResource = Config().getResource("Food");
            if (getInventoryResource(foodResource) > 0)
            {
                adjustInventoryResource(foodResource, -1);
                m_energy += 1;
            }
            else
            {
                //Out of food - die
                setSpeed(0);
            }
        }
    }
}

std::string Trader::outPutInventoryAsString()
{
    std::stringstream ss;
    ss <<getGP() << "gp\n";
     for(std::pair<const Resource *,int> resourceStockPair: getInventory())
    {
        ss << resourceStockPair.first->getName() << "(" <<resourceStockPair.second << ")\n";
    }
    return ss.str();
}

const std::unordered_map<Town *, std::shared_ptr<const Info> > &Trader::getAllHeldInfo() const
{
    return m_info->getAllHeldInfo();
}

void Trader::addInfo(const std::shared_ptr<const Info> & newInfo)
{
    m_info->addInfo(newInfo);
}

std::shared_ptr<const Info> Trader::addTownCurrentInfo(Town *town)
{
    return m_info->addTownCurrentInfo(town);
}

std::shared_ptr<const Info> Trader::getHeldInfoOnTown(Town * const town) const
{
    return m_info->getHeldInfoOnTown(town);
}

float length(const QPointF &p)
{
    return sqrtf(p.x()*p.x()+p.y()*p.y());
}

QPointF normalized(const QPointF &p)
{
    float len = length(p);
    return QPointF(p.x()/len,p.y()/len);
}

void Trader::setTargetVector(const QPointF &target)
{
    m_targetVector = target;
}

const QPointF &Trader::getTargetVector() const
{
    return m_targetVector;
}

void Trader::move(float speed)
{
    bool arrived = false;
    QPointF movementVector;
    if(length(m_targetVector) < speed)
    {
        arrived = true;
        movementVector = m_targetVector;
    }
    else
    {
        movementVector = normalized(m_targetVector)*speed;
    }
    moveBy(movementVector.x(),movementVector.y());
    m_targetVector -= movementVector;
    if(arrived)
        arrivedAtDestination();
}
