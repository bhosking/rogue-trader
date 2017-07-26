#include "map.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

#include "worldscene.h"

#define CHUNKSIZE 100

Map::Map(int height, int width)
    :m_height(height),
      m_width(width),
      m_verticalChunks((height/CHUNKSIZE)),
      m_horizontalChunks((width/CHUNKSIZE)),
      m_mapChunks(new QGraphicsPixmapItem[m_verticalChunks*m_horizontalChunks])

{
    QPixmap base(CHUNKSIZE,CHUNKSIZE);
    base.fill(QColor(0xEE,0xEE,0xAA,0xFE));
    base.fill(QColor(0xEE,0xEE,0xAA,0xFF));
    for(int i=0;i<m_verticalChunks;++i)
    {
        for(int j=0;j<m_horizontalChunks;++j)
        {
            m_mapChunks[i*m_horizontalChunks + j].setPixmap(base);
            m_mapChunks[i*m_horizontalChunks + j].setTransformationMode(Qt::SmoothTransformation);
            m_mapChunks[i*m_horizontalChunks + j].setZValue(2);
            m_mapChunks[i*m_horizontalChunks + j].setPos(j*CHUNKSIZE,i*CHUNKSIZE);

        }
    }
}

Map::~Map()
{
    delete[] m_mapChunks;
}

void Map::explore(QPointF pos, float radius)
{
    for(int x = -1;x<=1;++x)
    {
        for(int y = -1;y<=1;++y)
        {
            int chunkX = (int)(pos.x()/CHUNKSIZE) + x;
            int chunkY = (int)(pos.y()/CHUNKSIZE) + y;
            if(chunkX < 0 || chunkX >= m_horizontalChunks||chunkY < 0 || chunkY >= m_verticalChunks)
                continue;
            int chunkIndex = (chunkY*m_horizontalChunks + chunkX);
            QPixmap pixmap = m_mapChunks[chunkIndex].pixmap();
            QPainter p(&pixmap);
            QPointF relativePos = pos - QPointF(chunkX*CHUNKSIZE,chunkY*CHUNKSIZE);
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p.setRenderHint(QPainter::Antialiasing);
            p.setPen(Qt::NoPen);
            QRadialGradient gradient(relativePos,radius);
            gradient.setColorAt(0,Qt::transparent);
            gradient.setColorAt(0.8,Qt::transparent);
            gradient.setColorAt(1,QColor(0xEE,0xEE,0xAA,0xFF));
            p.setBrush(QBrush(gradient));
            p.drawEllipse(relativePos,radius,radius);
            m_mapChunks[chunkIndex].setPixmap(pixmap);
        }
    }

}

void Map::addToScene(WorldScene * worldScene)
{
    for(int i=0;i<m_verticalChunks*m_horizontalChunks;++i)
    {
        worldScene->addItem(&m_mapChunks[i]);
    }
}
