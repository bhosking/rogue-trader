#include "movablesceneitem.h"

float length(const QPointF &p)
{
    return sqrtf(p.x()*p.x()+p.y()*p.y());
}

QPointF normalized(const QPointF &p)
{
    float len = length(p);
    return QPointF(p.x()/len,p.y()/len);
}

MovableSceneItem::MovableSceneItem()
    :m_targetVector(0,0)
{

}

void MovableSceneItem::setTargetVector(const QPointF &target)
{
    m_targetVector = target;
}

const QPointF &MovableSceneItem::getTargetVector() const
{
    return m_targetVector;
}

void MovableSceneItem::move(float speed)
{
    bool arrived = false;
    QPointF movementVector;
    if(length(m_targetVector) < speed)
    {
        arrived = true;
        movementVector = m_targetVector;
    }
    else
    {
        movementVector = normalized(m_targetVector)*speed;
    }
    moveBy(movementVector.x(),movementVector.y());
    m_targetVector -= movementVector;
    if(arrived)
        arrivedAtDestination();
}
