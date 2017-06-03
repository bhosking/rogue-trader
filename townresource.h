#ifndef TOWNRESOURCE_H
#define TOWNRESOURCE_H
#include "resource.h"

class TownResource
{
public:
    TownResource();
    Resource const * resource;
    float rate;
    float stock;
    float buyPrice(int num = 1) const;
    float sellPrice(int num = 1) const;
    std::vector<std::pair<TownResource *,float> > townResourcesNeeded;
};

#endif // TOWNRESOURCE_H
