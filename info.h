#ifndef INFO_H
#define INFO_H
#include "resource.h"
#include "town.h"

class Info
{
public:
    Info(const Town *town, int tick);
    const std::vector<std::pair<const Resource *, int> > &getResources() const;
    int getTick() const;
    const Town *getTown() const;
    Info &operator= (const Info &other);
    bool isOlderThan(const Info &other) const;
private:
     const Town *m_town;
     int m_tick;
     std::vector<std::pair<const Resource *, int> > m_resources;
};

#endif // INFO_H
