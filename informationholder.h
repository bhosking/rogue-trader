#ifndef INFORMATIONHOLDER_H
#define INFORMATIONHOLDER_H
#include <unordered_map>
#include <memory>

class Town;
class Info;

class InformationHolder
{
public:
    InformationHolder();
    const std::unordered_map<const Town *, std::shared_ptr<const Info> > &getAllHeldInfo() const;
    /**
     * @brief getHeldInfoOnTown
     * Checks to see if there is information on the town and if so return it
     * @param town A pointer to a town object
     * @return A shared pointer to information on the town.
     * If this information holder has no information on the town the null shared_ptr is returned instead.
     */
    std::shared_ptr<const Info> getHeldInfoOnTown(const Town * town) const;

    void addInfo(const std::shared_ptr<const Info> &newInfo);
private:
    std::unordered_map<const Town *, std::shared_ptr<const Info> > m_info;
};

#endif // INFORMATIONHOLDER_H
