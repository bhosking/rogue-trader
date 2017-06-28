#include <qgraphicsitem.h>
#include <QGridLayout>
#include <QTabWidget>
#include <QTimer>
#include <QLabel>
#include "mainwindow.h"
#include "world.h"
#include "worldscene.h"
#include "worldviewer.h"
#include "sidewindow.h"
#include "playersceneitem.h"
#include "inventoryscreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_inventoryScreen(new InventoryScreen()),
    m_worldViewer(new WorldViewer()),
    m_gameTimer(new QTimer()),
    m_centralTabWidget(new QTabWidget()),
    m_sideWindow(new SideWindow)
{
    QWidget * widget = new QWidget(this);
    QGridLayout * gridLayout = new QGridLayout();
    widget->setLayout(gridLayout);
    m_centralTabWidget->addTab(m_worldViewer,"Map");
    m_centralTabWidget->addTab(m_inventoryScreen,"Inventory");
    gridLayout->addWidget(m_centralTabWidget,1,1);
    gridLayout->addWidget(m_sideWindow,1,2);

    setCentralWidget(widget);
    m_worldViewer->setScene(World::getWorld().getWorldScene());
    m_worldViewer->setDragMode(QGraphicsView::ScrollHandDrag);
    connect(m_gameTimer,SIGNAL(timeout()),this,SLOT(tickGame()));
    connect(World::getWorld().getPlayerSceneItem(),SIGNAL(arrivedAtTown(std::shared_ptr<const Info>, const std::unordered_map<const Resource *, int> &)),this,SLOT(pause()));
    connect(World::getWorld().getPlayerSceneItem(),SIGNAL(arrivedAtTown(std::shared_ptr<const Info>, const std::unordered_map<const Resource *, int> &)),m_sideWindow,SLOT(playerArrivedAtTown(std::shared_ptr<const Info>, const std::unordered_map<const Resource *, int> &)));

    connect(World::getWorld().getPlayerSceneItem(),SIGNAL(leftTown()),this,SLOT(unpause()));
    connect(World::getWorld().getPlayerSceneItem(),SIGNAL(leftTown()),m_sideWindow,SLOT(playerLeftTown()));

    connect(m_sideWindow,SIGNAL(buyWidgetClicked(const Resource*,int)),this,SLOT(PlayerTryBuyResource(const Resource*,int)));
    connect(m_sideWindow,SIGNAL(sellWidgetClicked(const Resource*,int)),this,SLOT(PlayerTrySellResource(const Resource*,int)));

    connect(World::getWorld().getPlayerSceneItem(), SIGNAL(inventoryChanged()), this, SLOT(refreshInventoryScreenInfo()));

    refreshInventoryScreenInfo();

    m_gameTimer->start(16);
}

MainWindow::~MainWindow()
{
}

void MainWindow::tickGame()
{
    World::getWorld().processTick(World::getWorld());
}

void MainWindow::pause()
{
    m_gameTimer->stop();
}

void MainWindow::unpause()
{
    m_gameTimer->start();
}

void MainWindow::PlayerTryBuyResource(const Resource * resource, int amount)
{
    World::getWorld().getPlayerSceneItem()->buy(resource,amount);
    refreshInventoryScreenInfo();
}

void MainWindow::PlayerTrySellResource(const Resource * resource, int amount)
{
    World::getWorld().getPlayerSceneItem()->sell(resource,amount);
    refreshInventoryScreenInfo();
}

void MainWindow::refreshInventoryScreenInfo()
{
    m_inventoryScreen->refreshInventory(World::getWorld().getPlayerSceneItem()->getInventory());
    m_inventoryScreen->setGold(World::getWorld().getPlayerSceneItem()->getGP());
}
