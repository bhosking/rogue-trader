#include "resource.h"
Resource::Resource(std::string name, float value, float mass, float volume, float decay)
    :m_name(name), m_value(value), m_mass(mass), m_volume(volume), m_decay(decay)
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
}
