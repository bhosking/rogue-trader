#include "worldviewer.h"

WorldViewer::WorldViewer()
{

}

void WorldViewer::enterEvent(QEvent *event)
{
    QGraphicsView::enterEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void WorldViewer::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}

void WorldViewer::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::ArrowCursor);
}
