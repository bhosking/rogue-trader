#include "trader.h"

Trader::Trader()
    :m_speed(1),m_stopped(false)
{

}

float Trader::getSpeed() const
{
    return m_speed;
}

void Trader::setSpeed(float newSpeed)
{
    m_speed = newSpeed;
}

bool Trader::isStopped() const
{
    return m_stopped;
}

void Trader::setStopped(bool stopped)
{
    m_stopped = stopped;
}

void Trader::processTick(World &)
{

}
