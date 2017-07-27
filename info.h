#ifndef INFO_H
#define INFO_H
#include <string>
#include <vector>

class Town;
class Resource;

class Info
{
public:
    Info(Town *town, int tick);
    const std::vector<std::pair<const Resource *, int> > &getResources() const;
    int getTick() const;
    Town *getTown() const;
    Info &operator= (const Info &other);
    bool isOlderThan(const Info &other) const;
    std::string getTownNameStockAndMedianPricesAsString() const;
    int getAgeOfInfo() const;
    int getPopulation() const;
    int getGP() const;
    int getValue() const;
    int getProfit(const Info &oldInfo, const Info &tradeInfo) const;
    std::vector<std::pair<const Resource *, int> > &getShoppingList(const Info &otherInfo, int gp) const;
    std::string getAgeOfInfoAsString() const;
private:
     Town *m_town;
     int m_population;
     int m_gp;
     int m_tick;
     std::vector<std::pair<const Resource *, int> > m_resources;
};

#endif // INFO_H
