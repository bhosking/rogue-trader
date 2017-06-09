#include <QGridLayout>
#include <QLabel>
#include "buyorsellwidget.h"
#include "sidewindow.h"
#include "resource.h"
#include "info.h"
#include "town.h"

SideWindow::SideWindow()
    :m_townNameLabel(new QLabel("<b>On the road again...</b>"))
{
    m_townNameLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    m_townNameLabel->setStyleSheet("font: 20pt;");
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(m_townNameLabel);
    setLayout(gridLayout);
    setMinimumWidth(300);

}

void SideWindow::setInfo(std::shared_ptr<const Info> newInfo)
{
    const std::vector<std::pair<const Resource *, int> >  & resources = newInfo->getResources();
    int i = 0;
    for(;i < resources.size();++i)
    {
        if(i >= m_buyWidgets.size())
        {
            m_buyWidgets.push_back(new BuyOrSellWidget(resources[i].first,resources[i].second,BuyOrSellWidget::Type::BUY,this));
            this->layout()->addWidget(m_buyWidgets[i]);
        }
        else
        {
            m_buyWidgets[i]->setStock(resources[i]);
            m_buyWidgets[i]->show();
        }
    }
    //hide any remainding unused widgets
    for(;i<m_buyWidgets.size();++i)
    {
        m_buyWidgets[i]->hide();
    }
    m_townNameLabel->setText("<b>"+QString(newInfo->getTown()->getName().c_str())+"</b>");
}

void SideWindow::playerArrivedAtTown(std::shared_ptr<const Info> info)
{
    setInfo(info);
}

void SideWindow::playerLeftTown()
{
    for(int i = 0;i<m_buyWidgets.size();++i)
    {
        m_buyWidgets[i]->hide();
    }
    m_townNameLabel->setText("<b>On the road again...</b>");
}
