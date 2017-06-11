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

    Config config = Config();
    for (const Resource *resource : config.getResources())
    {
        m_buyWidgets.push_back(new BuyOrSellWidget(resource, BuyOrSellWidget::Type::BUY, this));
        connect(m_buyWidgets.back(),SIGNAL(buyOrSellAmountOfResource(const Resource *, int)),this,SIGNAL(buyWidgetClicked(const Resource*,int)));
        m_buyTab->addWidget(m_buyWidgets.back());
        m_sellWidgets.push_back(new BuyOrSellWidget(resource, BuyOrSellWidget::Type::SELL, this));
        connect(m_sellWidgets.back(),SIGNAL(buyOrSellAmountOfResource(const Resource *, int)),this,SIGNAL(sellWidgetClicked(const Resource*,int)));
        m_sellTab->addWidget(m_sellWidgets.back());
    }
}

void SideWindow::setInfo(std::shared_ptr<const Info> newInfo, const std::unordered_map<const Resource *, int> &inventory)
{
    m_tabWidget->show();
    m_townNameLabel->setText("<b>"+QString(newInfo->getTown()->getName().c_str())+"</b>");
    //Note these resources must all be present in the correct order
    const std::vector<std::pair<const Resource *, int> >  & resources = newInfo->getResources();
    for(unsigned i = 0;i < resources.size();++i)
    {
        if (resources[i].second > 0)
        {
            m_buyWidgets[i]->setTownStock(resources[i]);
            m_buyWidgets[i]->setSelectedAmount(0);
            m_buyWidgets[i]->show();
        }
        else
        {
            m_buyWidgets[i]->hide();
        }
        std::unordered_map<const Resource *, int>::const_iterator inventoryResource = inventory.find(resources[i].first);
        if((inventoryResource!=inventory.end())&&((*inventoryResource).second > 0))
        {
            m_sellWidgets[i]->setPlayerStockAmount((*inventoryResource).second);
            m_sellWidgets[i]->setSelectedAmount(0);
            m_sellWidgets[i]->setTownStock(resources[i]);
            m_sellWidgets[i]->show();
        }
        else
        {
            m_sellWidgets[i]->hide();
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
