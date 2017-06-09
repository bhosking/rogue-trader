#ifndef PLAYERSCENEITEM_H
#define PLAYERSCENEITEM_H
#include "circularsceneitem.h"
#include "player.h"

class Info;

class PlayerSceneItem : public CircularSceneItem, public Player
{
    Q_OBJECT
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

signals:
    void arrivedAtTown(std::shared_ptr<const Info>);
    void leftTown();

private:
    float m_explorationRadius;
    QPointF m_movementDirection;
    QPointF m_targetVector;
    void move();
    void updateMovementDirection();

};

#endif // PLAYERSCENEITEM_H
