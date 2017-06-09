#ifndef INFO_H
#define INFO_H
#include <string>
#include <vector>

class Town;
class Resource;

class Info
{
public:
    Info(const Town *town, int tick);
    const std::vector<std::pair<const Resource *, int> > &getResources() const;
    int getTick() const;
    const Town *getTown() const;
    Info &operator= (const Info &other);
    bool isOlderThan(const Info &other) const;
    std::string getTownNameStockAndMedianPricesAsString() const;
    int getAgeOfInfo() const;
    std::string getAgeOfInfoAsString() const;
private:
     const Town *m_town;
     int m_tick;
     std::vector<std::pair<const Resource *, int> > m_resources;
};

#endif // INFO_H
