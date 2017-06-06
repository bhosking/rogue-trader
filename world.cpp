#include <QGraphicsSceneMouseEvent>
#include "world.h"
#include "map.h"
#include "config.h"
#include "worldscene.h"
#include "playersceneitem.h"
#include "townsceneitem.h"

World* World::m_instance = nullptr;
World::World()
    :m_worldScene(new WorldScene()),
      m_map(new Map()),
      m_playerSceneItem(new PlayerSceneItem()),
      m_tick(0)
{
    Config config = Config();
    addItemToWorld(m_map,QPointF(0,0));
    addItemToWorld(m_playerSceneItem,QPointF(50,50));
    std::vector<std::tuple<const Resource *, float, float> > resources;
    resources.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Food"), 1, 0));
    resources.push_back(std::tuple<const Resource *, float, float>
                        (config.getResource("Iron"), 0.25, 5));
    std::string name = "Test Town";
    TownSceneItem * testTown = new TownSceneItem(resources,100,name);
    addItemToWorld(testTown,QPointF(100,100));

    getMap()->explore(getPlayerSceneItem()->getPos(),getPlayerSceneItem()->getExplorationRadius());
}

WorldScene *World::getWorldScene()
{
    return m_worldScene;
}

Map *World::getMap()
{
    return m_map;
}

const PlayerSceneItem *World::getPlayerSceneItem()
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

const TownSceneItem *World::getTownSceneItemUnderMouse(QGraphicsSceneMouseEvent *event)
{
    const std::vector<TownSceneItem *> &towns = getTownSceneItems();
    const TownSceneItem * townUnderMouse = nullptr;
    for(const TownSceneItem * town: towns)
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
