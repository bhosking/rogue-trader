#ifndef TRADER_H
#define TRADER_H
#include <QPointF>
#include "updatableentity.h"
#include "informationholder.h"

class Town;

class Trader : public UpdatableEntity, public InformationHolder
{
public:
    Trader();
    virtual QPointF getPos() const = 0;
    float getSpeed() const;
    void setSpeed(float);
    bool isAtDestination() const;
    void setStoppedAtDestination(bool);
    const Town *getDestinationTown();
    void setDestinationTown(const Town *destination);
    void processTick(World &);

private:
    float m_speed;
    bool m_atDestination;
    const Town * m_destination;
};

#endif // TRADER_H
