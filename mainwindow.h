#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "world.h"
#include <QGraphicsView>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:
    void tickGame();
private:
    QGraphicsView * m_viewer;
    QTimer *m_gameTimer;
};

#endif // MAINWINDOW_H
