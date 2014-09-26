#include "GameMap.h"

const int GameMap::PLAYERS_MAX = 2;

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
    initPtsMap();
}

GameMap::GameMap(int m_width, int m_height, int m_seed)
{
    width = m_width;
    height = m_height;
    seed = m_seed;
    initTiles();
    initPtsMap();
}

GameMap::~GameMap()
{
    //todo
    //destroy all tiles!

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            delete tiles[y][x];
        }
    }
}

bool GameMap::contains(int x, int y)
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}

bool GameMap::contains(StiGame::Point& pt)
{
    return contains(pt.getX(), pt.getY());
}

void GameMap::initPtsMap(void)
{
    for(int i=0; i<PLAYERS_MAX; i++)
    {
        std::vector<StiGame::Point> v;
        startingPoints.insert(std::make_pair(i+1, v));
    }
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

PlayerMap* GameMap::GeneratePlayerMap(int playerId)
{
    PlayerMap *pmap = new PlayerMap(width, height);

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = get(x, y)->clone();
            pmap->addTile(y, t);
        }
    }

    return pmap;

}

void GameMap::addStartPoint(int player, StiGame::Point& pt)
{
    startingPoints[player].push_back(pt);
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

