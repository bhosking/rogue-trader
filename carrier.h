#ifndef CARRIER_H
#define CARRIER_H


class Carrier
{
public:
    Carrier();
    float getSpeed() const;
    float getEnergy() const;
    float getVitality() const;
    void setDesiredSpeed(float speed);
    void processTick();
private:
    float m_speed;
    float m_energy;
    float m_vitality;
    float m_maxSpeed;
};

#endif // CARRIER_H
