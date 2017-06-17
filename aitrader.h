#ifndef AITRADER_H
#define AITRADER_H

#include "trader.h"
#include "movablesceneitem.h"

class AITrader : public Trader, public MovableSceneItem
{
public:
    AITrader();
    void makeTrade();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void arrivedAtDestiniation();
    void processTick(World &);
    QPointF getPos() const;




};

#endif // AITRADER_H
