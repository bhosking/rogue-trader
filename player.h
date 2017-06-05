#ifndef PLAYER_H
#define PLAYER_H
#include <QPointF>
#include "updatableentity.h"
#include "trader.h"

class Player: public Trader
{
public:
    Player();
    void processTick(World &);
};

#endif // PLAYER_H
