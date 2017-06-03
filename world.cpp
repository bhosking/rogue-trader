#include "world.h"

World::World()
    :m_worldScene(new WorldScene()),
      m_map(new Map())
{
    m_worldScene->addItem(m_map);

}

WorldScene *World::getWorldScene()
{
    return m_worldScene;
}

Map *World::getMap()
{
    return m_map;
}



void World::processTick(World *)
{
    for(UpdatableEntity *entity:m_updatableEntities)
    {
        entity->processTick(this);
    }
}
