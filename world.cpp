#include "world.h"

World::World()
    :m_worldScene(new WorldScene()),
      m_map(new Map()),
      m_playerSceneItem(new PlayerSceneItem())
{
    addItemToWorld(m_map);
    addItemToWorld(m_playerSceneItem);
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

void World::addItemToWorld(QGraphicsItem *item)
{
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

void World::processTick(World *)
{
    for(UpdatableEntity *entity:m_updatableEntities)
    {
        entity->processTick(this);
    }
}
