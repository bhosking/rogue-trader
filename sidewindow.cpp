#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include "buyorsellwidget.h"
#include "sidewindow.h"
#include "resource.h"
#include "info.h"
#include "town.h"
#include "config.h"

SideWindow::SideWindow()
    :m_townNameLabel(new QLabel("<b>On the road again...</b>")),
      m_tabWidget(new QTabWidget()),
      m_buyAndSellResourcesTab(new QGridLayout()),
      m_buyAndSellInfoTab(new QGridLayout)
{
    m_townNameLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_townNameLabel->setStyleSheet("font: 20pt;");
    QVBoxLayout * vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(m_townNameLabel);

    QWidget * tab = new QWidget();
    tab->setLayout(m_buyAndSellResourcesTab);
    m_tabWidget->addTab(tab,"Resources");
    tab = new QWidget();
    tab->setLayout(m_buyAndSellInfoTab);
    m_tabWidget->addTab(tab,"Info");

    vBoxLayout->addWidget(m_tabWidget);
    setLayout(vBoxLayout);
    setMinimumWidth(320);

    m_tabWidget->hide();

    Config config = Config();
    for (const Resource *resource : config.getResources())
    {
        m_buyOrSellWidgets.push_back(new BuyOrSellWidget(resource, this));
        connect(m_buyOrSellWidgets.back(),SIGNAL(buyAmountOfResource(const Resource *, int)),this,SIGNAL(buyWidgetClicked(const Resource*,int)));
        connect(m_buyOrSellWidgets.back(),SIGNAL(sellAmountOfResource(const Resource *, int)),this,SIGNAL(sellWidgetClicked(const Resource*,int)));
        m_buyAndSellResourcesTab->addWidget(m_buyOrSellWidgets.back());
    }
}

void SideWindow::setInfo(std::shared_ptr<const Info> newInfo, const std::unordered_map<const Resource *, int> &inventory)
{
    m_tabWidget->show();
    m_townNameLabel->setText("<b>"+QString(newInfo->getTown()->getName().c_str())+"</b>");
    //Note these resources must all be present in the correct order
    const std::vector<std::pair<const Resource *, int> >  & resources = newInfo->getResources();
    int population = newInfo->getPopulation();
    const std::vector<const Resource *> allResources = Config().getResources();
    for(unsigned i = 0;i < allResources.size();++i)
    {
        m_buyOrSellWidgets[i]->setTownPopulation(population);

        std::unordered_map<const Resource *, int>::const_iterator inventoryResource = inventory.find(allResources[i]);
        //if either the town or the player has the resource
        if (resources[i].second > 0||(inventoryResource!=inventory.end()&&(*inventoryResource).second > 0))
        {
            m_buyOrSellWidgets[i]->setTownStock(resources[i]);
            if(inventoryResource!=inventory.end())
                m_buyOrSellWidgets[i]->setPlayerStockAmount((*inventoryResource).second);
            else
                m_buyOrSellWidgets[i]->setPlayerStockAmount(0);
            m_buyOrSellWidgets[i]->setSelectedAmount(0);
            m_buyOrSellWidgets[i]->show();
        }
        else
        {
            m_buyOrSellWidgets[i]->hide();
        }
    }
}

void SideWindow::playerArrivedAtTown(std::shared_ptr<const Info> info, const std::unordered_map<const Resource *, int> &inventory)
{
    setInfo(info,inventory);
}

void SideWindow::playerLeftTown()
{
    m_tabWidget->hide();
    m_townNameLabel->setText("<b>On the road again...</b>");
}
