#include <QGraphicsSceneMouseEvent>
#include <sstream>
#include "world.h"
#include "map.h"
#include "config.h"
#include "worldscene.h"
#include "playersceneitem.h"
#include "townsceneitem.h"
#include "aitrader.h"
#include "info.h"

World* World::m_instance = nullptr;
World::World()
    :m_worldScene(new WorldScene()),
      m_map(new Map()),
      m_playerSceneItem(new PlayerSceneItem()),
      m_tick(0)
{
    Config config = Config();
    m_worldScene->setBackgroundBrush(Qt::black);
    std::vector<std::tuple<const Resource *, float, float> > resources;
    resources.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Food"), 1, 0));
    resources.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Wood"), 0.5, 0));
    resources.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Iron"), 0.25, 5));
    std::string name = "Test Town";
    TownSceneItem * testTown = new TownSceneItem(resources,100,name);
    addItemToWorld(testTown,QPointF(100,100));
    std::vector<std::tuple<const Resource *, float, float> > resources2;
    resources2.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Food"), 0.5, 0));
    resources2.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Wood"), 0.8, 0));
    resources2.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Iron"), 0.5, 5));
    std::string name2 = "Test Town Two";
    TownSceneItem * testTown2 = new TownSceneItem(resources2,150,name2);
    addItemToWorld(testTown2,QPointF(150,200));
    std::vector<std::tuple<const Resource *, float, float> > resources3;
    resources3.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Food"), 1.5, 0));
    resources3.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Wood"), 0.2, 0));
    resources3.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Iron"), 0, 5));
    std::string name3 = "Test Town Three";
    TownSceneItem * testTown3 = new TownSceneItem(resources3,150,name3);
    addItemToWorld(testTown3,QPointF(200,100));

    addItemToWorld(m_map,QPointF(0,0));

    addItemToWorld(m_playerSceneItem,QPointF(50,50));

    m_playerSceneItem->adjustInventoryResource(config.getResource("Food"),100);
    getMap()->explore(getPlayerSceneItem()->getPos(),getPlayerSceneItem()->getExplorationRadius());

    //add traders
    AITrader * trader = new AITrader();
    trader->adjustInventoryResource(config.getResource("Food"),100);
    trader->addInfo(std::shared_ptr<const Info>(new Info(testTown, 0)));
    trader->addInfo(std::shared_ptr<const Info>(new Info(testTown2, 0)));
    trader->addInfo(std::shared_ptr<const Info>(new Info(testTown3, 0)));
    trader->setDestinationTown(testTown);
    addItemToWorld(trader,testTown->getPos());

}

WorldScene *World::getWorldScene()
{
    return m_worldScene;
}

Map *World::getMap()
{
    return m_map;
}

PlayerSceneItem *World::getPlayerSceneItem()
{
    return m_playerSceneItem;
}

const std::vector<TownSceneItem *> &World::getTownSceneItems()
{
    return m_townSceneItems;
}

int World::getTick() const
{
    return m_tick;
}

void World::addItemToWorld(QGraphicsItem * item,const QPointF &position)
{
    item->setPos(position);
    m_worldScene->addItem(item);
    UpdatableEntity * updatableEntity = dynamic_cast<UpdatableEntity*>(item);
    if(updatableEntity)
    {
        m_updatableEntities.push_back(updatableEntity);
    }

    TownSceneItem * townSceneItem = dynamic_cast<TownSceneItem*>(item);
    if(townSceneItem)
    {
        m_townSceneItems.push_back(townSceneItem);
    }
}

void World::removeItemFromWorld(QGraphicsItem *item)
{
    m_worldScene->removeItem(item);
    UpdatableEntity * updatableEntity = dynamic_cast<UpdatableEntity*>(item);
    if(updatableEntity)
    {
        m_updatableEntities.erase(std::find(m_updatableEntities.begin(),m_updatableEntities.end(),updatableEntity));
    }
    TownSceneItem * townSceneItem = dynamic_cast<TownSceneItem*>(item);
    if(townSceneItem)
    {
        m_townSceneItems.erase(std::find(m_townSceneItems.begin(),m_townSceneItems.end(),townSceneItem));
    }
    delete item;
}

TownSceneItem *World::getTownSceneItemUnderMouse(QGraphicsSceneMouseEvent *event)
{
    const std::vector<TownSceneItem *> &towns = getTownSceneItems();
    TownSceneItem * townUnderMouse = nullptr;
    for(TownSceneItem * town: towns)
    {
        if(town->contains(event->scenePos() - town->getPos()))
        {
            townUnderMouse = town;
        }
    }
    return townUnderMouse;
}

void World::processTick(World &)
{
    m_tick++;
    for(UpdatableEntity *entity:m_updatableEntities)
    {
        entity->processTick(*this);
    }
}

World &World::getWorld()
{
    if(m_instance==nullptr)
    {
        m_instance = new World();
    }

    return *m_instance;
}

std::string World::ticksToTime(int ticks, TimeFormat type)
{
    std::stringstream ss;
    int mins = ticks%60;
    ticks /= 60;
    int hours = ticks%24;
    int days = ticks/24;
    bool foundSomethingAlready = false;
    if(!(days==0&&type==TimeFormat::NON_ZERO)&&type==TimeFormat::DAYS)
    {
        addDaysToStringStream(days,&ss);
        foundSomethingAlready = true;
        if(type==TimeFormat::MOST_SIGNIFICANT)
            return ss.str();
    }
    if(!(hours==0&&type==TimeFormat::NON_ZERO)&&type==TimeFormat::HOURS)
    {
       if(foundSomethingAlready)
       {
            ss <<", ";
       }
       addHoursToStringStream(hours,&ss);
       if(type==TimeFormat::MOST_SIGNIFICANT)
           return ss.str();
    }
    if(!(mins==0&&type==TimeFormat::NON_ZERO)&&type==TimeFormat::MINUTES)
    {
        if(foundSomethingAlready)
        {
             ss <<", ";
        }
        addMinutesToStringStream(mins,&ss);
    }
    return ss.str();
}

void World::addDaysToStringStream(int days, std::stringstream *ss)
{
    (*ss) << days << " day";
    if(days!=1)
        (*ss) << "s";
}

void World::addHoursToStringStream(int hours, std::stringstream *ss)
{
    (*ss) << hours << " hour";
    if(hours!=1)
        (*ss) << "s";
}

void World::addMinutesToStringStream(int mins, std::stringstream *ss)
{
    (*ss) << mins << " minute";
    if(mins!=1)
        (*ss) << "s";
}
