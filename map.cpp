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
    setZValue(2);
}

Map::~Map()
{
    delete m_map;
}

void Map::explore(QPointF pos, float radius)
{
    QPainter p(m_map);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    QRadialGradient gradient(pos,radius);
    gradient.setColorAt(0,Qt::transparent);
    gradient.setColorAt(0.8,Qt::transparent);
    gradient.setColorAt(1,QColor(0xEE,0xEE,0xAA,0xFF));
    p.setBrush(QBrush(gradient));
    p.drawEllipse(pos,radius,radius);
    setPixmap(*m_map);
}
