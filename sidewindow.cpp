#include <QGridLayout>
#include <QPushButton>
#include "sidewindow.h"

SideWindow::SideWindow()
{
    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(new QPushButton("Test\nButton"));
    setLayout(gridLayout);
}
