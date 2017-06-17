#include "circularsceneitem.h"
float CircularSceneItem::m_radius = 10;

CircularSceneItem::CircularSceneItem()
{

}
QRectF CircularSceneItem::boundingRect() const
{
    float x = - m_radius  - 2;
    float y = - m_radius - 2;
    float width = 2 * m_radius + 4;
    float height = 2 * m_radius + 4;

    return QRectF(x,y,width,height);
}

bool CircularSceneItem::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    QPointF displacementVector = other->scenePos() - scenePos();
    return containedInCircleAtOrigin(displacementVector,m_radius*2);
}

bool CircularSceneItem::contains(const QPointF &point) const
{
    return containedInCircleAtOrigin(point,m_radius);
}

bool containedInCircleAtOrigin(const QPointF &p, float r)
{
    float x = p.x();
    float y = p.y();
    return x < r &&
            y < r &&
            x*x + y*y < r * r;
}
