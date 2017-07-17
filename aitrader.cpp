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
        addTownCurrentInfo(thisTown);
        int sold = -1;
        while(!getInventory().empty() && (sold != 0))
        {
            sold = sell(getInventory().begin()->first,getInventory().begin()->second);
        }
        //Buy some food to bring total food to 10 #dontstarve
        const Resource *foodResource = Config().getResource("Food");
        int foodAmount = getInventoryResource(foodResource);
        if (foodAmount < 10)
        {
            buy(foodResource, 10 - foodAmount);
        }
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
        if (bestOtherTown == nullptr)
        {
            // Oops, we're at a stalemate here, we probably have no money and as such aren't considering
            // any trading opportunities. TODO handle this more gracefully. For now, maybe the town couldn't
            // buy our goods, so we'll go somewhere with more money. Or at least somewhere.
            int thisTownGP = thisTownInfo->getGP();
            for (std::pair<Town *, std::shared_ptr<const Info> > townInfo : getAllHeldInfo())
            {
                bestOtherTown = townInfo.first;
                if (townInfo.second->getGP() > thisTownGP)
                {
                    break;
                }
            }
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
    painter->setPen(QPen(Qt::cyan,2));
    painter->drawEllipse(QPointF(),m_radius,m_radius);

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
    setVisible(canBeSeenByPlayer(world));
}
