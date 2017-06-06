#include <qgraphicsitem.h>
#include <QGridLayout>
#include <QTabWidget>
#include <QTimer>
#include "mainwindow.h"
#include "world.h"
#include "worldscene.h"
#include "worldviewer.h"
#include "sidewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_worldViewer(new WorldViewer()),
    m_gameTimer(new QTimer()),
    m_centralTabWidget(new QTabWidget()),
    m_sideWindow(new SideWindow)
{
    QWidget * widget = new QWidget(this);
    QGridLayout * gridLayout = new QGridLayout();
    widget->setLayout(gridLayout);
    m_centralTabWidget->addTab(m_worldViewer,"Map");
    gridLayout->addWidget(m_centralTabWidget,1,1);
    gridLayout->addWidget(m_sideWindow,1,2);

    setCentralWidget(widget);
    m_worldViewer->setScene(World::getWorld().getWorldScene());
    m_worldViewer->setDragMode(QGraphicsView::ScrollHandDrag);
    connect(m_gameTimer,SIGNAL(timeout()),this,SLOT(tickGame()));
    m_gameTimer->start(16);
}

MainWindow::~MainWindow()
{
}

void MainWindow::tickGame()
{
    World::getWorld().processTick(World::getWorld());
}
