#include "map.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
Map::Map()
    :m_map(new QPixmap(512,512))
{
    m_map->fill(QColor(0xEE,0xEE,0xAA));
    setPixmap(*m_map);
    setTransformationMode(Qt::SmoothTransformation);
}

Map::~Map()
{
    delete m_map;
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    explore(event->scenePos(),20);
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    explore(event->scenePos(),20);
}

void Map::explore(QPointF pos, float radius)
{
    QPainter p(m_map);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black,Qt::SolidPattern));
    p.drawEllipse(pos,radius,radius);
    setPixmap(*m_map);
}
