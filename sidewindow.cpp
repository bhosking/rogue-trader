#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include "buyorsellwidget.h"
#include "sidewindow.h"
#include "resource.h"
#include "info.h"
#include "town.h"

SideWindow::SideWindow()
    :m_townNameLabel(new QLabel("<b>On the road again...</b>")),
      m_tabWidget(new QTabWidget()),
      m_buyTab(new QGridLayout()),
      m_sellTab(new QGridLayout)
{
    m_townNameLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_townNameLabel->setStyleSheet("font: 20pt;");
    QVBoxLayout * vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(m_townNameLabel);

    QWidget * tab = new QWidget();
    tab->setLayout(m_buyTab);
    m_tabWidget->addTab(tab,"Buy");
    tab = new QWidget();
    tab->setLayout(m_sellTab);
    m_tabWidget->addTab(tab,"Sell");

    vBoxLayout->addWidget(m_tabWidget);
    setLayout(vBoxLayout);
    setMinimumWidth(320);

    m_tabWidget->hide();

}

void SideWindow::setInfo(std::shared_ptr<const Info> newInfo, const std::unordered_map<const Resource *, int> &inventory)
{
    m_tabWidget->show();
    m_townNameLabel->setText("<b>"+QString(newInfo->getTown()->getName().c_str())+"</b>");
    int numberOfSellWidgets = 0;
    //set up buy widgets
    const std::vector<std::pair<const Resource *, int> >  & resources = newInfo->getResources();
    int i = 0;
    for(;i < resources.size();++i)
    {
        //set up buy widgets
        if(i >= m_buyWidgets.size())
        {
            m_buyWidgets.push_back(new BuyOrSellWidget(resources[i].first,resources[i].second,BuyOrSellWidget::Type::BUY,this));
            connect(m_buyWidgets[i],SIGNAL(buyOrSellAmountOfResource(const Resource *, int)),this,SIGNAL(buyWidgetClicked(const Resource*,int)));
            m_buyTab->addWidget(m_buyWidgets[i]);
        }
        else
        {
            m_buyWidgets[i]->setTownStock(resources[i]);
        }
        m_buyWidgets[i]->setSelectedAmount(0);
        //set up sell widgets
        std::unordered_map<const Resource *, int>::const_iterator inventoryResource = inventory.find(resources[i].first);
        if(inventoryResource!=inventory.end())
        {
            if(i >= m_sellWidgets.size())
            {
                m_sellWidgets.push_back(new BuyOrSellWidget(resources[i].first,resources[i].second,BuyOrSellWidget::Type::SELL,this));
                connect(m_sellWidgets[i],SIGNAL(buyOrSellAmountOfResource(const Resource *, int)),this,SIGNAL(sellWidgetClicked(const Resource*,int)));
                m_sellTab->addWidget(m_sellWidgets[numberOfSellWidgets]);
            }
            else
            {
                m_sellWidgets[numberOfSellWidgets]->setTownStock(resources[i]);
            }
            m_sellWidgets[numberOfSellWidgets]->setPlayerStockAmount((*inventoryResource).second);
            m_sellWidgets[numberOfSellWidgets]->setSelectedAmount(0);

            numberOfSellWidgets++;
        }
    }
    //hide any remainding unused buy widgets
    for(;i<m_buyWidgets.size();++i)
    {
        m_buyWidgets[i]->hide();
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
