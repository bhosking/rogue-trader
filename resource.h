#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <utility>
#include <string>


class Resource
{
public:
    Resource(std::string name,float value,float mass,float volume);
    const std::string & getName() const;
    float getValue() const;
    float getMass() const;
    float getVolume() const;
    const std::vector<std::pair<const Resource *, float> > & getNeeds() const;
    void addNeed(const Resource *, float requiredAmount);
    void setValue(float newValue);

private:
    Resource(){}
    std::string m_name;
    float m_value;
    float m_mass;
    float m_volume;
    std::vector<std::pair<const Resource*,float> > m_needs;

};

#endif // RESOURCE_H
//[Resource names]
//Food
//Iron
//Tools
//Weapons
//
//[Food]
//value=214
//
//
