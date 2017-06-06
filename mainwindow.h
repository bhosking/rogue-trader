#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WorldViewer;
class QTabWidget;
class QTimer;
class SideWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void tickGame();
private:
    WorldViewer * m_worldViewer;
    QTabWidget *m_centralTabWidget;
    QTimer *m_gameTimer;
    SideWindow *m_sideWindow;
};

#endif // MAINWINDOW_H
