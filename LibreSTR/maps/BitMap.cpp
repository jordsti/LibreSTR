#include "BitMap.h"

BitMap::BitMap(int m_width, int m_height)
{
    rows = (m_height / 8) + 1;
    cols = (m_width / 8) + 1;

    initTiles();
}

BitMap::BitMap(ITileMap *map)
{
    rows = (map->getHeight() / 8) + 1;
    cols = (map->getWidth() / 8) + 1;

    initTiles();

    for(int r=0; r<map->getHeight(); r++)
    {
        for(int c=0; c<map->getWidth(); c++)
        {
            setTile(c, r, map->get(c, r)->getType() == TT_Normal);
        }
    }
}

BitMap::~BitMap()
{

}

void BitMap::setTile(int x, int y, bool val)
{
    int row_i = y / 8;
    int col_i = x / 8;

    int inner_row = y % 8;
    int inner_col = x % 8;

    unsigned int bitmask = inner_row * 8 + inner_col;

    unsigned int tile_val = tiles[row_i][col_i];

    if(val)
    {
        tile_val = tile_val ^ bitmask;
    }
    else
    {
        tile_val = tile_val | bitmask;
    }

    tiles[row_i][col_i] = tile_val;
}

bool BitMap::getTile(int x, int y)
{
    int row_i = y / 8;
    int col_i = x / 8;

    int inner_row = y % 8;
    int inner_col = x % 8;

    unsigned int bitmask = inner_row * 8 + inner_col;

    unsigned int tile_val = tiles[row_i][col_i];

    return (tile_val & bitmask == bitmask);
}

void BitMap::initTiles(void)
{
    for(int i=0; i<rows; i++)
    {
        std::vector<unsigned int> row;

        for(int j=0; j<cols; j++)
        {
            row.push_back(0);
        }

        tiles.push_back(row);
    }
}
