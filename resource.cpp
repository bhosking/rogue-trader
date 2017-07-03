#include <math.h>
#include <limits>
#include "resource.h"
Resource::Resource(std::string name, float value, float mass, float volume, float halfPrice, float consume, std::string iconName)
    :m_name(name), m_value(value), m_mass(mass), m_volume(volume), m_decay(-1 / halfPrice),
      m_consume(consume), m_iconName(iconName)
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

float Resource::getDecay(int population) const
{
    return population != 0 ? m_decay/population : m_decay;
}

float Resource::getConsume() const
{
    return m_consume;
}

const std::vector<std::pair<const Resource *, float> > &Resource::getNeeds() const
{
    return m_needs;
}

const std::string &Resource::getIconName() const
{
    return m_iconName;
}

void Resource::addNeed(const Resource * resource, float requiredAmount)
{
    m_needs.push_back(std::pair<const Resource *, float>(resource,requiredAmount));
}

void Resource::setValue(float newValue)
{
    m_value = newValue;
}

int Resource::outPrice(int startStock, int population, int num) const
{
    return lrint(getBulkValue(startStock - num, population, num));
}

int Resource::inPrice(int startStock, int population, int num) const
{
    return lrint(getBulkValue(startStock, population, num));
}

int Resource::howMuchCanIBuy(int startStock, int population, int gp) const
{
    float decay = getDecay(population);
    return static_cast<int>(-1 * log2(gp * (1-exp2(decay))/(getValue() * exp2(decay * startStock)) + 1) / decay);
}

int Resource::howMuchCanISell(int startStock, int population, int gp) const
{
    float decay = getDecay(population);
    return static_cast<int>(log2(1 - gp * (1-exp2(decay))/(getValue() * exp2(decay * startStock))) / decay);
}

int Resource::getMaxTradeAmount(int stockA, int populationA, int stockB, int populationB) const
{
    float decayA = getDecay(populationA);
    float decayB = getDecay(populationB);
    return static_cast<int>((stockA * decayA - stockB * decayB) / (decayA + decayB));
}

float Resource::getRelativeDifference(int stockA, int populationA, int stockB, int populationB) const
{
    return stockB * getDecay(populationB) - stockA * getDecay(populationA);
}

float Resource::getBulkValue(int startStock, int population, int deltaStock) const
{
    float decay = getDecay(population);
    return getValue() * exp2(decay * startStock) * (1 - exp2(deltaStock * decay)) / (1-exp2(decay));
}
