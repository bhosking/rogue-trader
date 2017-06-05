#ifndef UPDATABLEENTITY_H
#define UPDATABLEENTITY_H
class World;

class UpdatableEntity
{
public:
    UpdatableEntity(){}
    virtual void processTick(World &) = 0;
};

#endif // UPDATABLEENTITY_H
