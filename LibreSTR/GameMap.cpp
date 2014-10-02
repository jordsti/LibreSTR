#include "GameMap.h"
#include <fstream>


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

void GameMap::load(std::string input, AssetManager *asset)
{
    std::ifstream in (input.c_str(), std::ifstream::in | std::ifstream::binary);

    MapHeader header;

    in.read((char*)&header, sizeof(header));

    width = header.width;
    height = header.height;
    seed = header.seed;

    initTiles();

    TileInfo ti;

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            in.read((char*)&ti, sizeof(TileInfo));
            Tile *t = get(x, y);
            t->setType(static_cast<TileType>(ti.type));

            if(ti.type == TT_Normal)
            {
                t->setTexture(asset->getTileNormal());
            }
            else if(ti.type == TT_Block)
            {
                t->setTexture(asset->getTileBlock());
            }
        }
    }

    ResourceMarker rmark;

    in.read((char*)&rmark, sizeof(ResourceMarker));

    ResourceInfo ri;

    for(int i=0; i<rmark.count; i++)
    {
        in.read((char*)&ri, sizeof(ResourceInfo));
        Tile *t = get(ri.x, ri.y);
        if(ri.type == RT_METAL)
        {
            t->setResource(asset->getMetalDef()->create());

        }
        else if(ri.type == RT_GAZ)
        {
            t->setResource(asset->getGazDef()->create());
        }

        t->getResource()->setAmount(ri.amount);
    }

    in.close();
}

void GameMap::save(std::string output)
{
    std::ofstream out (output.c_str(), std::ofstream::out | std::ofstream::binary);

    //writing map header
    MapHeader header;
    header.width = width;
    header.height = height;
    header.seed = seed;

    out.write(reinterpret_cast<char*>(&header), sizeof(MapHeader));

    TileInfo ti;

    std::vector<StiGame::Point> resPts;

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = get(x, y);
            ti.type = t->getType();
            out.write(reinterpret_cast<char*>(&ti), sizeof(TileInfo));

            if(t->containsResource())
            {
                resPts.push_back(StiGame::Point(x, y));
            }
        }
    }

    ResourceMarker rmark;
    rmark.count = resPts.size();
    out.write(reinterpret_cast<char*>(&rmark), sizeof(ResourceMarker));

    auto lit(resPts.begin()), lend(resPts.end());
    for(;lit!=lend;++lit)
    {
        Tile *t = get((*lit).getX(), (*lit).getY());
        IResource *r = t->getResource();

        ResourceInfo ri;
        ri.x = (*lit).getX();
        ri.y = (*lit).getY();
        ri.amount = r->getAmount();
        ri.type = r->getType();

        out.write(reinterpret_cast<char*>(&ri), sizeof(ResourceInfo));
    }

    out.close();


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

