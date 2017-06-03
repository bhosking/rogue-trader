#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <pair>


class Resource
{
public:
    Resource();
    std::string name;
    float value;
    float mass;
    float volume;
    std::vector<std::pair<Resource*,float> > needs;

}

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
