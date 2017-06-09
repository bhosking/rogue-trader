#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <utility>
#include <string>


class Resource
{
public:
    Resource(std::string name,float value,float mass,float volume,float halfPrice);
    const std::string & getName() const;
    float getValue() const;
    float getMass() const;
    float getVolume() const;
    float getDecay() const;
    float getDecayConstant() const;
    const std::vector<std::pair<const Resource *, float> > & getNeeds() const;
    void addNeed(const Resource *, float requiredAmount);
    void setValue(float newValue);
    int outPrice(int startStock, int num = 1) const;
    int inPrice(int startStock, int num = 1) const;
    int howMuchCanIBuy(int startStock, int gp) const;
private:
    float getBulkValue(int startStock, int deltaStock = 1) const;
    void setDecayConstant();

    Resource() = default;
    std::string m_name;
    float m_value;
    float m_mass;
    float m_volume;
    float m_decay;
    float m_decayConstant;
    std::vector<std::pair<const Resource*,float> > m_needs;

};

#endif // RESOURCE_H
