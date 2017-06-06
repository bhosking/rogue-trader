#include "trader.h"

Trader::Trader()
    :m_speed(1),m_atDestination(true),m_destination(nullptr)
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

bool Trader::isAtDestination() const
{
    return m_atDestination;
}

void Trader::setStoppedAtDestination(bool stopped)
{
    m_atDestination = stopped;
}

const Town *Trader::getDestinationTown()
{
    return m_destination;
}

void Trader::setDestinationTown(const Town * destination)
{
    m_destination = destination;
}

void Trader::processTick(World &)
{

}
