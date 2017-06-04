#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),m_viewer(new QGraphicsView()),m_world(new World()),m_gameTimer(new QTimer())
{
    setCentralWidget(m_viewer);
    m_viewer->setScene(m_world->getWorldScene());
    connect(m_gameTimer,SIGNAL(timeout()),this,SLOT(tickGame()));
    m_gameTimer->start(16);
}

MainWindow::~MainWindow()
{
}

void MainWindow::tickGame()
{
    m_world->processTick(m_world);
}
