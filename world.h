#ifndef WORLD_H
#define WORLD_H
#include "updatableentity.h"
#include <vector>
#include <qpoint.h>
#include <string>

class QGraphicsSceneMouseEvent;
class QGraphicsItem;
class Map;
class TownSceneItem;
class PlayerSceneItem;
class WorldScene;

enum class TimeFormat
{
    DAYS = 1,
    HOURS = 2,
    MINUTES = 4,
    NON_ZERO = 8,
    MOST_SIGNIFICANT = 16,
    DAYS_HOURS_AND_MINUTES = 7
};

inline TimeFormat operator|(TimeFormat a, TimeFormat b)
{return static_cast<TimeFormat>(static_cast<int>(a) | static_cast<int>(b));}
inline bool operator==(TimeFormat a, TimeFormat b)
{return static_cast<int>(a) & static_cast<int>(b);}
inline bool operator!=(TimeFormat a, TimeFormat b)
{return !(a==b);}

class World : public UpdatableEntity
{
public:

    WorldScene * getWorldScene();
    Map * getMap();
    PlayerSceneItem * getPlayerSceneItem();
    const std::vector<TownSceneItem *> &getTownSceneItems();

    int getTick() const;

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
    void addItemToWorld(QGraphicsItem * item,const QPointF &position);

    /**
     * @brief Removes item from World
     *
     * This function removes the item from the world and deletes it.
     * The item should not exist anywhere after calling this function
     * as long as the item was added with addItemToWorld()
     * @param item
     */
    void removeItemFromWorld(QGraphicsItem * item);

    /**
     * @brief getTownSceneItemUnderMouse
     * This function checks to see if a mouse event is over a TownSceneItem and if so returns a pointer to it.
     * @param event A pointer to the QGraphicsSceneMouseEvent which will be checked.
     * @return A pointer to the TownSceneItem that the mouse is over, if the mouse is not above a TownSceneItem nullptr is returned.
     */
    TownSceneItem *getTownSceneItemUnderMouse(QGraphicsSceneMouseEvent *event);

    void processTick(World &);
    static World &getWorld();
    static std::string ticksToTime(int ticks,TimeFormat type = TimeFormat::MOST_SIGNIFICANT|TimeFormat::DAYS_HOURS_AND_MINUTES|TimeFormat::NON_ZERO);
private:
    static void addDaysToStringStream(int days, std::stringstream * ss);
    static void addHoursToStringStream(int hours, std::stringstream * ss);
    static void addMinutesToStringStream(int mins, std::stringstream * ss);

    World();
    WorldScene * m_worldScene;
    Map * m_map;
    PlayerSceneItem * m_playerSceneItem;
    std::vector<UpdatableEntity*> m_updatableEntities;
    std::vector<TownSceneItem*> m_townSceneItems;
    int m_tick;
    static World * m_instance;
};

#endif // WORLD_H
