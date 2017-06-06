#ifndef PLAYERSCENEITEM_H
#define PLAYERSCENEITEM_H
#include "circularsceneitem.h"
#include "player.h"

class PlayerSceneItem : public CircularSceneItem, public Player
{
public:
    PlayerSceneItem();
    QPointF getPos() const;
    float getExplorationRadius() const;
    void setExplorationRadius(float newRadius);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void processTick(World &);
private:
    float m_explorationRadius;
    QPointF m_movementDirection;
    QPointF m_targetVector;
    void move();
    void updateMovementDirection();

};

#endif // PLAYERSCENEITEM_H
