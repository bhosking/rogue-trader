#ifndef PLAYERSCENEITEM_H
#define PLAYERSCENEITEM_H
#include "trader.h"

class Info;

class PlayerSceneItem : public Trader
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
    void updateTownInfo();
    virtual void buy(const Resource *resource, int amount);
    virtual void sell(const Resource *resource, int amount);
    void arrivedAtDestination();
signals:
    void arrivedAtTown(std::shared_ptr<const Info>, const std::unordered_map<const Resource *, int> & inventory);
    void leftTown();

private:
    float m_explorationRadius;

};

#endif // PLAYERSCENEITEM_H
