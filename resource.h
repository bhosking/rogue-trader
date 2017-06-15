#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <utility>
#include <string>


class Resource
{
public:
    Resource(std::string name,float value,float mass,float volume,float halfPrice, float consume, std::string iconName);
    const std::string & getName() const;
    float getValue() const;
    float getMass() const;
    float getVolume() const;
    float getDecay(int population) const;
    float getConsume() const;
    const std::vector<std::pair<const Resource *, float> > & getNeeds() const;
    const std::string &getIconName() const;
    void addNeed(const Resource *, float requiredAmount);
    void setValue(float newValue);
    int outPrice(int startStock, int population, int num = 1) const;
    int inPrice(int startStock, int population, int num = 1) const;
    int howMuchCanIBuy(int startStock, int population, int gp) const;
    int getMaxTradeAmount(int stockA, int populationA, int stockB, int populationB) const;
private:
    float getBulkValue(int startStock, int population, int deltaStock = 1) const;

    Resource() = default;
    std::string m_name;
    float m_value;
    float m_mass;
    float m_volume;
    float m_decay;
    float m_consume;
    std::string m_iconName;
    std::vector<std::pair<const Resource*,float> > m_needs;

};

#endif // RESOURCE_H
