#ifndef BITMAP_H
#define BITMAP_H
#include <vector>
#include "ITileMap.h"
class BitMap
{
public:
    BitMap(int m_width, int m_height);
    BitMap(ITileMap *map);
    virtual ~BitMap();

    void setTile(int x, int y, bool val);
    bool getTile(int x, int y);
private:
    void initTiles(void);
    std::vector< std::vector<unsigned int> > tiles;
    int rows;
    int cols;

    int width;
    int height;
};

#endif // BITMAP_H
