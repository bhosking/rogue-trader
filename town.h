#ifndef TOWN_H
#define TOWN_H
#include "updatableentity.h"
#include "unordered_map"

class Town : public UpdatableEntity
{
public:
    Town();
    void processTick(World *);
private:

};

#endif // TOWN_H
