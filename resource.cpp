#include <math.h>
#include <limits>
#include "resource.h"
Resource::Resource(std::string name, float value, float mass, float volume, float halfPrice)
    :m_name(name), m_value(value), m_mass(mass), m_volume(volume), m_decay(-1 / halfPrice),
      m_decayConstant(m_value/(1-exp2(m_decay)))
{

}

const std::string &Resource::getName() const
{
    return m_name;
}

float Resource::getValue() const
{
    return m_value;
}

float Resource::getMass() const
{
    return m_mass;
}

float Resource::getVolume() const
{
    return m_volume;
}

float Resource::getDecay() const
{
    return m_decay;
}

float Resource::getDecayConstant() const
{
    return m_decayConstant;
}

const std::vector<std::pair<const Resource *, float> > &Resource::getNeeds() const
{
    return m_needs;
}

void Resource::addNeed(const Resource * resource, float requiredAmount)
{
    m_needs.push_back(std::pair<const Resource *, float>(resource,requiredAmount));
}

void Resource::setValue(float newValue)
{
    m_value = newValue;
    setDecayConstant();
}

int Resource::outPrice(int startStock, int num) const
{
    return lrint(getBulkValue(startStock - num, num));
}

int Resource::inPrice(int startStock, int num) const
{
    return lrint(getBulkValue(startStock, num));
}

int Resource::howMuchCanIBuy(int startStock, int gp) const
{
    float d = gp/(getDecayConstant() * exp2(getDecay() * startStock));
    if(d>=1)
        return std::numeric_limits<int>::max();
    return static_cast<int>(log2(1 - d) / getDecay());
}

float Resource::getBulkValue(int startStock, int deltaStock) const
{
    return exp2(getDecay() * startStock) * (1 - exp2(deltaStock * getDecay())) * getDecayConstant();
}

void Resource::setDecayConstant()
{
    m_decayConstant = getValue() / (1-exp2(getDecay()));
}
