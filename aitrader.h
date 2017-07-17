#ifndef AITRADER_H
#define AITRADER_H

#include "trader.h"

class AITrader : public Trader
{
public:
    AITrader();
    void makeTrade();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void arrivedAtDestination();
    void processTick(World &world);




};

#endif // AITRADER_H
