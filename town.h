#ifndef TOWN_H
#define TOWN_H
#include "updatableentity.h"
#include "unordered_map"

class Town : public updatableEntity
{
public:
    Town();
    processTick();
private:

};

#endif // TOWN_H
