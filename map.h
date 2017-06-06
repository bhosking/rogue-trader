#ifndef MAP_H
#define MAP_H
#include <QGraphicsPixmapItem>


class Map : public QGraphicsPixmapItem
{
public:
    Map();
    ~Map();
    void explore(QPointF pos, float radius);

private:
    QPixmap *m_map;
};

#endif // MAP_H
