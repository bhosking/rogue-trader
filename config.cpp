#include "config.h"

Config::Config()
{
    loadResources();
}

const std::unordered_map<std::string, Resource *> &Config::getResources() const
{
    return m_resources;
}

const Resource *Config::getResource(std::string name) const
{
    return getResources().at(name);
}

void Config::loadResources()
{
    std::vector <Resource *> resources;
    // Resource Declaration
    // Parameters are name, value, mass, volume, halfPrice
    resources.push_back(new Resource("Food", 10, 1, 2, 100));
    resources.push_back(new Resource("Iron", 40, 1, 0.5, 50));

    for (Resource * resource : resources) {
        m_resources[resource->getName()] = resource;
    }
    // Resource Needs
    m_resources.at("Iron")->addNeed(getResource("Food"), 3);
}
