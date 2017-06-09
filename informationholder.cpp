#include "informationholder.h"
#include "info.h"
#include "world.h"

InformationHolder::InformationHolder()
{

}

const std::unordered_map<const Town *, std::shared_ptr<const Info> > &InformationHolder::getAllHeldInfo() const
{
    return m_info;
}

void InformationHolder::addInfo(const std::shared_ptr<const Info> & newInfo)
{
    m_info[newInfo->getTown()] = newInfo;
}

std::shared_ptr<const Info> InformationHolder::addTownCurrentInfo(const Town *town)
{
    m_info[town] = std::shared_ptr<const Info>(new Info(town, World::getWorld().getTick()));
    return m_info[town];
}

std::shared_ptr<const Info> InformationHolder::getHeldInfoOnTown(const Town * const town) const
{
    auto townInfo = m_info.find(town);
    if(townInfo==m_info.end())
    {
        return std::shared_ptr<const Info>();
    }
    else
        return std::shared_ptr<const Info>(townInfo->second);
}
