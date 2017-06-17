#ifndef MOVABLESCENEITEM_H
#define MOVABLESCENEITEM_H
#include "circularsceneitem.h"

class MovableSceneItem: public CircularSceneItem
{
public:
    MovableSceneItem();
    void setTargetVector(const QPointF & target);
    const QPointF &getTargetVector() const;
    void move(float speed);
    virtual void arrivedAtDestination() = 0;

private:
    QPointF m_targetVector;
};

#endif // MOVABLESCENEITEM_H
