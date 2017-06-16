#include "aitrader.h"
#include "info.h"
#include "resource.h"

AITrader::AITrader()
{

}

void AITrader::makeTrade()
{
    Town *thisTown = getDestinationTown();
    if (isAtDestination() && thisTown)
    {
        std::shared_ptr<const Info> thisTownInfo = addTownCurrentInfo(thisTown);
        for (std::pair<const Resource *, int> resourceStock : getInventory())
        {
            sell(resourceStock.first, resourceStock.second);
        }
        int gp = getGP();
        //Naively calculate greatest profit -> largest relative price difference
        const Town *bestOtherTown = nullptr;
        const Resource *bestResource = nullptr;
        int bestThisStock = 0;
        int bestOtherStock = 0;
        int bestOtherTownPopulation = 0;
        float bestProfit = 0;
        int thisTownPopulation = thisTownInfo->getPopulation();
        const std::vector<std::pair<const Resource *, int> > thisTownResources = thisTownInfo->getResources();
        for (int i=0; i<thisTownResources.size(); i++)
        {
            const Resource *resource = thisTownResources[i].first;
            int thisStock = thisTownResources[i].second;
            if (gp > resource->outPrice(thisStock, thisTownPopulation))
            {
                for (std::pair<const Town *, std::shared_ptr<const Info> > townInfo : getAllHeldInfo())
                {
                    const Town *otherTown = townInfo.first;
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
            // Go trade with bestOtherTown
        }
        else
        {
            // No good trades available from this town, go exploring?
        }
    }
}
