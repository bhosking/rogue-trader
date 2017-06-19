#include <algorithm>
#include "carrier.h"

Carrier::Carrier()
{

}

float Carrier::getSpeed() const
{
    return m_speed;
}

float Carrier::getEnergy() const
{
    return m_energy;
}

float Carrier::getVitality() const
{
    return m_vitality;
}

void Carrier::setDesiredSpeed(float speed)
{
    m_speed = std::min(speed, m_maxSpeed);
}

void Carrier::processTick()
{

}
