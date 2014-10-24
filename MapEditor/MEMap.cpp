#include "MEMap.h"

using namespace STRData;
using namespace StiGame;

MEMap::MEMap(int m_width, int m_height, STRData::MapData *mapData)
{
    width = m_width;
    height = m_height;

    tileDimension = Dimension(TILE_WIDTH, TILE_HEIGHT);
    initTiles();

    if(mapData != nullptr)
    {
        //todo
        //copy from this
    }
}

MEMap::~MEMap()
{

}

METile* MEMap::getTile(int t_x, int t_y)
{
    return &tiles[t_y][t_x];
}

StiGame::Dimension* MEMap::getTileDimension(void)
{
    return &tileDimension;
}

int MEMap::getWidth(void)
{
    return width;
}

int MEMap::getHeight(void)
{
    return height;
}

void MEMap::initTiles(void)
{
    for(int y=0; y<height; y++)
    {
        std::vector < METile > row;
        for(int x=0; x<width; x++)
        {
            METile t;
            row.push_back(t);
        }
        tiles.push_back(row);
    }
}


