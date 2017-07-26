#ifndef MAP_H
#define MAP_H
#include <QGraphicsPixmapItem>

class WorldScene;

class Map
{
public:
    Map(int height, int width);
    ~Map();
    void explore(QPointF pos, float radius);
    void addToScene(WorldScene*);
private:
    int m_height;
    int m_width;
    int m_verticalChunks;
    int m_horizontalChunks;
    QGraphicsPixmapItem *m_mapChunks;

};

#endif // MAP_H
