#include "carriedresource.h"

CarriedResource::CarriedResource(const Resource *resource)
    :m_amount(0),m_resource(resource)
{

}

void CarriedResource::addAmount(int amountToAdd)
{
    m_amount += amountToAdd;
}

void CarriedResource::removeAmount(int amountToRemove)
{
    m_amount -= amountToRemove;
}

int CarriedResource::getAmount()
{
    return m_amount;
}

void CarriedResource::setAmount(int newAmount)
{
    m_amount = newAmount;
}

float CarriedResource::getMass()
{
    return m_resource->getMass()*m_amount;
}

float CarriedResource::getVolume()
{
    return m_resource->getVolume()*m_amount;

}

const Resource *CarriedResource::getResource()
{
    return m_resource;
}
