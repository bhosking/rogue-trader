#include "config.h"
#include "resource.h"

Config::Config()
{
    loadResources();
}

const std::vector<const Resource *> &Config::getResources() const
{
    return m_resources;
}

const Resource *Config::getResource(std::string name) const
{
    for (const Resource *resource : getResources())
    {
        if (resource->getName() == name)
        {
            return resource;
        }
    }
    return nullptr;
}

void Config::loadResources()
{
    std::vector <Resource *> resources;
    // Resource Declaration
    // Parameters are name, value, mass, volume, halfPrice
    resources.push_back(new Resource("Food", 10, 1, 2, 100, ":/images/Food.svg"));
    resources.push_back(new Resource("Wood", 6, 10, 5, 400, ":/images/Wood.svg"));
    resources.push_back(new Resource("Iron", 40, 1, 0.5, 50, ":/images/Steel.svg"));

    for (Resource * resource : resources) {
        std::string name=resource->getName();
        // Resource Needs
        if (name=="Iron")
        {
            resource->addNeed(getResource("Food"), 3);
        }
        m_resources.push_back(resource);
    }
}
