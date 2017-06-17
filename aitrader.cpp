#include <QPainter>
#include "aitrader.h"
#include "info.h"
#include "resource.h"
#include "town.h"

AITrader::AITrader()
{

}

void AITrader::makeTrade()
{
    Town *thisTown = getDestinationTown();
    if (isAtDestination() && thisTown)
    {
        for (std::pair<const Resource *, int> resourceStock : getInventory())
        {
            sell(resourceStock.first, resourceStock.second);
        }
        int gp = getGP();
        //Naively calculate greatest profit -> largest relative price difference
        Town *bestOtherTown = nullptr;
        const Resource *bestResource = nullptr;
        int bestThisStock = 0;
        int bestOtherStock = 0;
        int bestOtherTownPopulation = 0;
        float bestProfit = 0;
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
                    }
                }
            }
        }
        if (bestResource) {
            buy(bestResource, bestResource->getMaxTradeAmount(bestThisStock, thisTownPopulation, bestOtherStock, bestOtherTownPopulation));
            setTargetVector(bestOtherTown->getPos()-getPos());
            setDestinationTown(bestOtherTown);
            // Go trade with bestOtherTown
        }
        else
        {
            // No good trades available from this town, go exploring?
        }
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
    painter->drawLine(QPointF(0,0),getTargetVector());
}

void AITrader::arrivedAtDestiniation()
{
    makeTrade();
}

void AITrader::processTick(World &)
{
    move(getSpeed());
}

QPointF AITrader::getPos() const
{
    return scenePos();
}
