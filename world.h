#ifndef WORLD_H
#define WORLD_H
#include "map.h"
#include "playersceneitem.h"
#include "townsceneitem.h"
#include "worldscene.h"
#include "updatableentity.h"
#include <vector>


class World : public UpdatableEntity
{
public:
    World();
    WorldScene * getWorldScene();
    Map * getMap();
    const PlayerSceneItem * getPlayerSceneItem();
    const std::vector<TownSceneItem *> &getTownSceneItems();

    /**
     * @brief addItemToWorld and takes ownership of the pointer
     * adds item to world and any relevant vectors it belongs to.
     *
     * For example if someone is working on the vector of
     * TownSceneItem pointers received from getTownSceneItems()
     * and adds a TownSceneItem with addItemToWorld();
     * That item will also be added to the vector they are
     * working with automatically.
     * @param item to add
     */
    void addItemToWorld(QGraphicsItem * item);

    /**
     * @brief Removes item from World
     *
     * This function removes the item from the world and deletes it.
     * The item should not exist anywhere after calling this function
     * as long as the item was added with addItemToWorld()
     * @param item
     */
    void removeItemFromWorld(QGraphicsItem * item);
    void processTick(World *);
private:
    Map * m_map;
    PlayerSceneItem * m_playerSceneItem;
    WorldScene * m_worldScene;
    std::vector<UpdatableEntity*> m_updatableEntities;
    std::vector<TownSceneItem*> m_townSceneItems;

};

#endif // WORLD_H
