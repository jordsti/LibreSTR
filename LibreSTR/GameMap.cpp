#include "GameMap.h"

GameMap::GameMap()
{
    width = 0;
    height = 0;
    seed = 0;
}

GameMap::GameMap(int m_width, int m_height)
{
    width = m_width;
    height = m_height;
    seed = 0;
    initTiles();
}

GameMap::GameMap(int m_width, int m_height, int m_seed)
{
    width = m_width;
    height = m_height;
    seed = m_seed;
    initTiles();
}

GameMap::~GameMap()
{
    //todo
    //destroy all tiles!
}

void GameMap::initTiles()
{
    for(int r=0; r<height; r++)
    {
        std::vector<Tile*> row;

        for(int c=0; c<width; c++)
        {
            Tile *t = new Tile();
            row.push_back(t);
        }

        tiles.push_back(row);
    }
}

int GameMap::getWidth(void)
{
    return width;
}

int GameMap::getHeight(void)
{
    return height;
}

int GameMap::getSeed(void)
{
    return seed;
}

Tile* GameMap::get(int x, int y)
{
    return tiles[y][x];
}

