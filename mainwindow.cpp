#include "mainwindow.h"
#include <qgraphicsview.h>
#include <qgraphicsitem.h>
#include "world.h"
#include "worldscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),m_viewer(new QGraphicsView()),m_gameTimer(new QTimer())
{
    setCentralWidget(m_viewer);
    m_viewer->setScene(World::getWorld().getWorldScene());
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
