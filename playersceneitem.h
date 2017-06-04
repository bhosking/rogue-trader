#ifndef PLAYERSCENEITEM_H
#define PLAYERSCENEITEM_H
#include <qgraphicsitem.h>
#include "player.h"

class PlayerSceneItem : public QGraphicsItem, public Player
{
public:
    PlayerSceneItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QRectF boundingRect() const;
    void processTick(World * world);
private:
    QPointF m_targetVector;
    void updateMovementDirection();

};

#endif // PLAYERSCENEITEM_H