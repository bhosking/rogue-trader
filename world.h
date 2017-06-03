#ifndef WORLD_H
#define WORLD_H
#include "map.h"
#include "worldscene.h"
#include "updatableentity.h"
#include <vector>


class World : public UpdatableEntity
{
public:
    World();
    WorldScene * getWorldScene();
    Map * getMap();
    void processTick(World *);
private:
    Map * m_map;
    WorldScene * m_worldScene;
    std::vector<UpdatableEntity*> m_updatableEntities;

};

#endif // WORLD_H
