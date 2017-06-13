#include "map.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
Map::Map()
    :m_map(new QPixmap(512,512))
{
    m_map->fill(QColor(0xEE,0xEE,0xAA,0xFE));
    m_map->fill(QColor(0xEE,0xEE,0xAA,0xFF));
    setPixmap(*m_map);
    setTransformationMode(Qt::SmoothTransformation);
}

Map::~Map()
{
    delete m_map;
}

void Map::explore(QPointF pos, float radius)
{
    QPainter p(m_map);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::transparent);
    p.setBrush(QBrush(Qt::transparent,Qt::SolidPattern));
    p.drawEllipse(pos,radius,radius);
    setPixmap(*m_map);
}
