#ifndef TRADER_H
#define TRADER_H
#include "updatableentity.h"

class Trader : public UpdatableEntity
{
public:
    Trader();
    float getSpeed() const;
    void setSpeed(float);
    bool isStopped() const;
    void setStopped(bool);
    void processTick(World &);

private:
    float m_speed;
    bool m_stopped;
};

#endif // TRADER_H
