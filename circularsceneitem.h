#ifndef CIRCULARSCENEITEM_H
#define CIRCULARSCENEITEM_H
#include <QGraphicsItem>

class CircularSceneItem : public QGraphicsObject
{
public:
    CircularSceneItem();
    QRectF boundingRect() const;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    bool contains(const QPointF &point) const;
    static float m_radius;
};
bool containedInCircleAtOrigin(const QPointF &p,float r);

#endif // CIRCULARSCENEITEM_H
