#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include "buyorsellwidget.h"
#include "resource.h"
BuyOrSellWidget::BuyOrSellWidget(const Resource *resource, int stock , Type type , QWidget *parent)
    :m_buyOrSellAmountSlider(new QSlider()),
      m_resource(resource),
      m_buyOrSellButton(new QPushButton()),
      m_unitPriceLabel(new QLabel()),
      m_totalPriceLabel(new QLabel()),
      m_stock(stock),
      m_selectedAmount(0),
      m_type(type)
{
    m_buyOrSellAmountSlider->setOrientation(Qt::Horizontal);
    int maxTextWidth = m_unitPriceLabel->fontMetrics().width("Unit Price: "+QString::number(m_resource->outPrice(0)));
    m_unitPriceLabel->setMinimumWidth(maxTextWidth);
    maxTextWidth = m_totalPriceLabel->fontMetrics().width("Total Price: "+QString::number(m_resource->outPrice(m_stock,m_stock)));
    m_totalPriceLabel->setMinimumWidth(maxTextWidth);

    if(m_type==Type::BUY)
    {
        m_buyOrSellAmountSlider->setMaximum(m_stock);
        m_buyOrSellButton->setText("Buy");
    }
    setSelectedAmount(0);
    QGroupBox *groupBox = new QGroupBox(m_resource->getName().c_str());
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(m_buyOrSellAmountSlider,0,0,1,3);
    gridLayout->addWidget(m_unitPriceLabel,1,0);
    gridLayout->addWidget(m_totalPriceLabel,1,1);
    gridLayout->addWidget(m_buyOrSellButton,1,2);
    groupBox->setLayout(gridLayout);
    setLayout(new QGridLayout());
    this->layout()->addWidget(groupBox);

    connect(m_buyOrSellButton,SIGNAL(clicked(bool)),this,SIGNAL(buyOrSellButtonPressed()));
    connect(m_buyOrSellAmountSlider,SIGNAL(valueChanged(int)),this,SLOT(setSelectedAmount(int)));
}

int BuyOrSellWidget::getSelectedAmount()
{
    return m_selectedAmount;
}

void BuyOrSellWidget::setSelectedAmount(int newAmount)
{

    m_selectedAmount = newAmount>m_stock ? m_stock : newAmount;

    if(m_buyOrSellAmountSlider->value()!=m_selectedAmount)
    {
        m_buyOrSellAmountSlider->setValue(m_selectedAmount);
    }
    if(m_type==Type::BUY)
    {
        m_unitPriceLabel->setText("Unit Price: " + QString::number(m_resource->outPrice(m_stock-m_selectedAmount)));
        m_totalPriceLabel->setText("Total Price: " + QString::number(m_resource->outPrice(m_stock,m_selectedAmount)));
        m_buyOrSellButton->setText("Buy " + QString::number(m_selectedAmount));
    }
}

void BuyOrSellWidget::setStockAmount(int newStockAmount)
{
    m_stock = newStockAmount;
    m_buyOrSellAmountSlider->setMaximum(m_stock);
    setSelectedAmount(m_selectedAmount);
}

void BuyOrSellWidget::setStock(const std::pair<const Resource *, int> &stock)
{
    m_resource = stock.first;
    setStockAmount(stock.second);
}
