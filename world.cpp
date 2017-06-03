#include "world.h"

World::World()
    :m_worldScene(new WorldScene()),
      m_map(new Map()),
      m_playerSceneItem(new PlayerSceneItem())
{
    m_worldScene->addItem(m_map);
    m_worldScene->addItem(m_playerSceneItem);
    m_updatableEntities.push_back(m_playerSceneItem);
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

void World::processTick(World *)
{
    for(UpdatableEntity *entity:m_updatableEntities)
    {
        entity->processTick(this);
    }
}
