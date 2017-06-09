#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WorldViewer;
class QTabWidget;
class QTimer;
class SideWindow;
class Resource;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tickGame();
    void pause();
    void unpause();
    void PlayerTryBuyResource(const Resource *resource, int amount);
    void PlayerTrySellResource(const Resource *resource, int amount);

private:
    WorldViewer * m_worldViewer;
    QTabWidget *m_centralTabWidget;
    QTimer *m_gameTimer;
    SideWindow *m_sideWindow;
};

#endif // MAINWINDOW_H
