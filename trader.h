#ifndef TRADER_H
#define TRADER_H
#include <QPointF>
#include "updatableentity.h"
#include "informationholder.h"

class Trader : public UpdatableEntity, public InformationHolder
{
public:
    Trader();
    virtual QPointF getPos() const = 0;
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
