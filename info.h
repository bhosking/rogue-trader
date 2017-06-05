#ifndef INFO_H
#define INFO_H
#include "resource.h"
#include "town.h"

class Info
{
public:
    Info();
    const std::vector<std::pair<const Resource *, int> > & getResources();
    void update(const Info info);
private:
     unsigned m_tick;
     std::vector<std::pair<const Resource *, int> > m_resources;
};

#endif // INFO_H
