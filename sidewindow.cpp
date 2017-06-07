#include <QGridLayout>
#include "buyorsellwidget.h"
#include "sidewindow.h"
#include "resource.h"

SideWindow::SideWindow()
{
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(new BuyOrSellWidget(new Resource("FooBarium Expensive",10000,0.5,0.5,50),100,BuyOrSellWidget::Type::BUY));
    gridLayout->addWidget(new BuyOrSellWidget(new Resource("FooBarium Cheap",10,0.5,0.5,50),100,BuyOrSellWidget::Type::BUY));
    gridLayout->addWidget(new BuyOrSellWidget(new Resource("FooBarium high Decay",1000,0.5,0.5,10),100,BuyOrSellWidget::Type::BUY));
    gridLayout->addWidget(new BuyOrSellWidget(new Resource("FooBarium",100,0.5,0.5,50),100,BuyOrSellWidget::Type::BUY));
    gridLayout->addWidget(new BuyOrSellWidget(new Resource("FooBarium",100,0.5,0.5,50),100,BuyOrSellWidget::Type::BUY));

    setLayout(gridLayout);
}
