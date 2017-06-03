#ifndef PLAYER_H
#define PLAYER_H
#include "updatableentity.h"
#include <QPointF>

class Player: public UpdatableEntity
{
public:
    Player();
    void setSpeed(float);
    void processTick(World *);

protected:
    QPointF m_movementDirection;
    float m_speed;
    bool m_stopped;
};

#endif // PLAYER_H
