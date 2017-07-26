#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QSvgWidget>
#include "buyorsellwidget.h"
#include "resource.h"
BuyOrSellWidget::BuyOrSellWidget(const Resource *resource, QWidget *parent)
    :m_buyOrSellAmountSlider(new QSlider()),
      m_resource(resource),
      m_buyOrSellButton(new QPushButton()),
      m_unitPriceLabel(new QLabel()),
      m_totalPriceLabel(new QLabel()),
      m_townStock(0),
      m_selectedAmount(0),
      m_svg(new QSvgWidget(QString::fromStdString(resource->getIconName())))
{
    m_buyOrSellAmountSlider->setOrientation(Qt::Horizontal);
    int maxTextWidth = m_unitPriceLabel->fontMetrics().width("Unit Price: "+QString::number(m_resource->outPrice(0, 1)));
    m_unitPriceLabel->setMinimumWidth(maxTextWidth);
    maxTextWidth = m_totalPriceLabel->fontMetrics().width("Total Price: "+QString::number(m_resource->outPrice(m_townStock, 1, m_townStock)));
    m_totalPriceLabel->setMinimumWidth(maxTextWidth);
    m_svg->setFixedSize(64, 64);

    setSelectedAmount(0);
    QGroupBox *groupBox = new QGroupBox(m_resource->getName().c_str());
    QGridLayout * gridLayout = new QGridLayout();

    gridLayout->addWidget(m_svg, 0, 0);
    gridLayout->addWidget(m_buyOrSellAmountSlider,1,0,1,3);
    gridLayout->addWidget(m_unitPriceLabel,2,0);
    gridLayout->addWidget(m_totalPriceLabel,2,1);
    gridLayout->addWidget(m_buyOrSellButton,2,2);
    groupBox->setLayout(gridLayout);
    setLayout(new QGridLayout());
    this->layout()->addWidget(groupBox);

    connect(m_buyOrSellButton,SIGNAL(clicked(bool)),this,SLOT(buyOrSellButtonPressed()));
    connect(m_buyOrSellAmountSlider,SIGNAL(valueChanged(int)),this,SLOT(setSelectedAmount(int)));
}

int BuyOrSellWidget::getSelectedAmount()
{
    return m_selectedAmount;
}

void BuyOrSellWidget::setSelectedAmount(int newAmount)
{
    m_selectedAmount = newAmount;
    update();
    if(newAmount > m_townStock)
        m_selectedAmount = m_townStock;
    if(-newAmount > m_playerStock)
        m_selectedAmount = m_playerStock;
}

void BuyOrSellWidget::buyOrSellButtonPressed()
{
    if(m_selectedAmount>0)
        emit buyAmountOfResource(m_resource,m_selectedAmount);
    if(m_selectedAmount<0)
        emit sellAmountOfResource(m_resource,-m_selectedAmount);
}

void BuyOrSellWidget::setTownStockAmount(int newTownStockAmount)
{
    m_townStock = newTownStockAmount;
    m_buyOrSellAmountSlider->setMaximum(m_townStock);
    update();
}

void BuyOrSellWidget::setTownStock(const std::pair<const Resource *, int> &stock)
{
    m_resource = stock.first;
    setTownStockAmount(stock.second);
}

void BuyOrSellWidget::setPlayerStockAmount(int newPlayerStockAmount)
{
    m_playerStock = newPlayerStockAmount;
    m_buyOrSellAmountSlider->setMinimum(-m_playerStock);
    update();
}

void BuyOrSellWidget::setTownPopulation(int population)
{
    m_townPopulation = population;
}

void BuyOrSellWidget::update()
{

    if(m_selectedAmount > m_townStock)
        m_selectedAmount = m_townStock;
    if(-m_selectedAmount > m_playerStock)
        m_selectedAmount = m_playerStock;

    if(m_buyOrSellAmountSlider->value()!=m_selectedAmount)
    {
        m_buyOrSellAmountSlider->setValue(m_selectedAmount);
    }

    if(m_selectedAmount>=0)
    {
        m_unitPriceLabel->setText("Unit Price: " + QString::number(m_resource->outPrice(m_townStock-m_selectedAmount, m_townPopulation)));
        m_totalPriceLabel->setText("Total Price: " + QString::number(m_resource->outPrice(m_townStock, m_townPopulation, m_selectedAmount)));
        m_buyOrSellButton->setText("Buy " + QString::number(m_selectedAmount));
    }
    else
    {
        m_unitPriceLabel->setText("Unit Price: " + QString::number(m_resource->inPrice(m_townStock+(-m_selectedAmount), m_townPopulation)));
        m_totalPriceLabel->setText("Total Price: " + QString::number(m_resource->inPrice(m_townStock, m_townPopulation, (-m_selectedAmount))));
        m_buyOrSellButton->setText("Sell " + QString::number((-m_selectedAmount)));
    }
}
