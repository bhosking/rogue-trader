#ifndef WORLDVIEWER_H
#define WORLDVIEWER_H
#include <QGraphicsView>

class WorldViewer : public QGraphicsView
{
public:
    WorldViewer();
protected:
    void enterEvent(QEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // WORLDVIEWER_H
