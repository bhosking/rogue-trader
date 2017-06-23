#include <QPainter>
#include "aitrader.h"
#include "info.h"
#include "resource.h"
#include "town.h"
#include "config.h"

AITrader::AITrader()
{

}

void AITrader::makeTrade()
{
    Town *thisTown = getDestinationTown();
    if (isAtDestination() && thisTown)
    {
        while(!getInventory().empty())
        {
            sell(getInventory().begin()->first,getInventory().begin()->second);
        }
        //Buy some food to bring total food to 10 #dontstarve
        buy(Config().getResource("Food"), 10);
        int gp = getGP();
        //Naively calculate greatest profit -> largest relative price difference
        Town *bestOtherTown = nullptr;
        const Resource *bestResource = nullptr;
        int bestThisStock = 0;
        int bestOtherStock = 0;
        int bestOtherTownPopulation = 0;
        float bestProfit = 0;
        float cheapestProfit = 0;
        Town *cheapestOtherTown = nullptr;
        std::shared_ptr<const Info> thisTownInfo = getHeldInfoOnTown(thisTown);
        int thisTownPopulation = thisTownInfo->getPopulation();
        const std::vector<std::pair<const Resource *, int> > thisTownResources = thisTownInfo->getResources();
        for (int i=0; i<thisTownResources.size(); i++)
        {
            const Resource *resource = thisTownResources[i].first;
            int thisStock = thisTownResources[i].second;
            if (gp > resource->outPrice(thisStock, thisTownPopulation))
            {
                for (std::pair<Town *, std::shared_ptr<const Info> > townInfo : getAllHeldInfo())
                {
                    Town *otherTown = townInfo.first;
                    if (otherTown != thisTown)
                    {
                        std::shared_ptr<const Info> otherTownInfo = townInfo.second;
                        int otherStock = otherTownInfo->getResources()[i].second;
                        int otherTownPopulation = otherTownInfo->getPopulation();
                        float profit = resource->getRelativeDifference(thisStock, thisTownPopulation, otherStock, otherTownPopulation);
                        if (profit > bestProfit)
                        {
                            bestOtherTown = otherTown;
                            bestResource = resource;
                            bestThisStock = thisStock;
                            bestOtherStock = otherStock;
                            bestOtherTownPopulation = otherTownPopulation;
                            bestProfit = profit;
                        }
                        else if (profit < cheapestProfit)
                        {
                            cheapestOtherTown = otherTown;
                            cheapestProfit = profit;
                        }
                    }
                }
            }
        }
        if (bestResource) {
            buy(bestResource, bestResource->getMaxTradeAmount(bestThisStock, thisTownPopulation, bestOtherStock, bestOtherTownPopulation));
        }
        else
        {
            // No good trades available from this town, go exploring?
            //go to the town with the largest relative price difference (cheaper than here)
            bestOtherTown = cheapestOtherTown;
        }
        setTargetVector(bestOtherTown->getPos()-getPos());
        setDestinationTown(bestOtherTown);
        setStoppedAtDestination(false);
        // Go trade with bestOtherTown
    }
}

void AITrader::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
    painter->setPen(QPen(Qt::darkBlue,2));
    if(isAtDestination()&&getDestinationTown())
    {
        painter->drawEllipse(QPointF(),m_radius+2,m_radius+2);
    }
    else
    {
        painter->drawEllipse(QPointF(),m_radius,m_radius);
    }
}

void AITrader::arrivedAtDestination()
{
    setStoppedAtDestination(true);
    makeTrade();
}

void AITrader::processTick(World &world)
{
    Trader::processTick(world);
    move(getSpeed());
}

QPointF AITrader::getPos() const
{
    return scenePos();
}
