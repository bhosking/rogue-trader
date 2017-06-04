#ifndef TOWNSCENEITEM_H
#define TOWNSCENEITEM_H
#include <QGraphicsItem>
#include "town.h"

class TownSceneItem :public QGraphicsItem, public Town
{
public:
    TownSceneItem();
};

#endif // TOWNSCENEITEM_H
