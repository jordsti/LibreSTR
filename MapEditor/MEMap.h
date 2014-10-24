#ifndef MEMAP_H
#define MEMAP_H

#include <vector>
#include <Dimension.h>
#include "METile.h"

class MEMap
{
public:
    MEMap(int m_width, int m_height, STRData::MapData *mapData = nullptr);
    virtual ~MEMap();

    int getWidth(void);
    int getHeight(void);

    METile* getTile(int t_x, int t_y);

    StiGame::Dimension* getTileDimension(void);
protected:
    StiGame::Dimension tileDimension;

    int width;
    int height;
    void initTiles(void);
    std::vector < std::vector< METile > > tiles;

};

#endif // MEMAP_H
