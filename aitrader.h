#ifndef AITRADER_H
#define AITRADER_H

#include "trader.h"


class AITrader : public Trader
{
public:
    AITrader();
    void makeTrade();
};

#endif // AITRADER_H
