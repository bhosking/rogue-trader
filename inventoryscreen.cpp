#include <QTableWidgetItem>
#include <QSvgWidget>
#include <QLabel>
#include <QGridLayout>
#include "inventoryscreen.h"
#include "resource.h"
#include "config.h"


struct InventoryRow
{
     InventoryRow()
         :m_resource(nullptr),
           m_image(nullptr),
           m_nameLabel(new QLabel("Resource")),
           m_volumeLabel(new QLabel("Volume")),
           m_massLabel(new QLabel("Mass")),
           m_amountLabel(new QLabel("Quantity"))

     {
        m_nameLabel->setStyleSheet("font-size: 20px; font-style: bold");
        m_volumeLabel->setStyleSheet("font-size: 20px; font-style: bold");
        m_massLabel->setStyleSheet("font-size: 20px; font-style: bold");
        m_amountLabel->setStyleSheet("font-size: 20px; font-style: bold");
     }

    InventoryRow(const Resource * resource)
        :m_resource(resource),
          m_image(new QSvgWidget(QString::fromStdString(resource->getIconName()))),
          m_nameLabel(new QLabel(QString::fromStdString(resource->getName()))),
          m_volumeLabel(new QLabel("0")),
          m_massLabel(new QLabel("0")),
          m_amountLabel(new QLabel("0"))
    {
        hide();
        m_image->setFixedSize(32, 32);

        m_nameLabel->setStyleSheet("font-size: 16px");
        m_volumeLabel->setStyleSheet("font-size: 16px");
        m_massLabel->setStyleSheet("font-size: 16px");
        m_amountLabel->setStyleSheet("font-size: 16px");
    }

    void show()
    {
        m_image->show();
        m_nameLabel->show();
        m_volumeLabel->show();
        m_massLabel->show();
        m_amountLabel->show();
    }

    void hide()
    {
        m_image->hide();
        m_nameLabel->hide();
        m_volumeLabel->hide();
        m_massLabel->hide();
        m_amountLabel->hide();
    }

    void setAmount(int newAmount)
    {
        hide();
        m_volumeLabel->setText(QString::number(newAmount*m_resource->getVolume(),'f',1));
        m_massLabel->setText(QString::number(newAmount*m_resource->getMass(),'f',1));
        m_amountLabel->setText(QString::number(newAmount));
        if(newAmount!=0)
            show();
    }

    void addToGridLayout(QGridLayout * layout, int row)
    {
        if(m_resource)
        {
            layout->addWidget(m_image,row,0,1,1);
            layout->addWidget(m_nameLabel,row,1,1,1);
        }
        else
        {
            layout->addWidget(m_nameLabel,row,0,1,2);
        }
        layout->addWidget(m_volumeLabel,row,2,1,1,Qt::AlignRight);
        layout->addWidget(m_massLabel,row,3,1,1,Qt::AlignRight);
        layout->addWidget(m_amountLabel,row,4,1,1,Qt::AlignRight);
    }

    const Resource * m_resource;
    QSvgWidget * m_image;
    QLabel * m_nameLabel;
    QLabel * m_volumeLabel;
    QLabel * m_massLabel;
    QLabel * m_amountLabel;

};

InventoryScreen::InventoryScreen()
    :m_headerRow(new InventoryRow())
{
    Config config = Config();
    QGridLayout * layout = new QGridLayout();
    m_headerRow->addToGridLayout(layout,0);
    int row = 1;
    for (const Resource *resource : config.getResources())
    {
        InventoryRow * invRow = new InventoryRow(resource);
        invRow->addToGridLayout(layout,row);
        m_currentInv.push_back(invRow);
        row++;
    }
    layout->setRowStretch(row,1);
    setLayout(layout);
}

void InventoryScreen::refreshInventory(const std::unordered_map<const Resource *, int> &inv)
{
    for(int i = 0; i < m_currentInv.size();++i)
    {
        auto it = inv.find(m_currentInv[i]->m_resource);
        if(it==inv.end())
        {
            m_currentInv[i]->setAmount(0);
        }
        else
        {
            m_currentInv[i]->setAmount(it->second);
        }
    }
}
