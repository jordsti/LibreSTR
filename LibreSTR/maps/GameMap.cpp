#include "GameMap.h"
#include <fstream>
#include <set>
#include <map>
#include <cmath>
#include <cstring>

const int GameMap::PLAYERS_MAX = 2;

GameMap::GameMap()
{
    width = 0;
    height = 0;
    seed = 0;
    defaultTexture = 0;
}

GameMap::GameMap(int m_width, int m_height)
{
    width = m_width;
    height = m_height;
    seed = 0;
    defaultTexture = 0;
    initTiles();
    initPtsMap();
}

GameMap::GameMap(int m_width, int m_height, int m_seed)
{
    width = m_width;
    height = m_height;
    seed = m_seed;
    defaultTexture = 0;
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

std::vector<StiGame::Point>& GameMap::getPlayerStartingPoints(int index)
{
    return startingPoints[index];
}

int GameMap::getGroundUnitsCount(void)
{
    return units.size();
}

MGroundUnit* GameMap::getGroundUnit(int index)
{
    return units[index];
}

int GameMap::getBuildingsCount(void)
{
    return buildings.size();
}

MBuilding* GameMap::getBuilding(int index)
{
    return buildings[index];
}

bool GameMap::placeUnit(MGroundUnit *unit, int pt_x, int pt_y)
{
    unit->setPoint(pt_x, pt_y);
    StiGame::Point mpt = unit->middle();

    //not inside a building
    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->contains(mpt.getX(), mpt.getY()))
        {
            return false;
        }
    }

    auto vit2(units.begin()), vend2(units.end());
    for(;vit2!=vend2;++vit2)
    {
        int length = (int)(*vit2)->distanceWith(&mpt);
        if(length < unit->getSize())
        {
            return false;
        }
    }

    //placing
    units.push_back(unit);
    return true;
}

bool GameMap::placeBuilding(MBuilding *building, int t_x, int t_y)
{
    float t_w = (float)(building->getWidth()) / (float)Tile::TILE_WIDTH;
    float t_h = (float)(building->getHeight()) / (float)Tile::TILE_HEIGHT;

    int it_w = (int)ceil(t_w);
    int it_h = (int)ceil(t_h);

    for(int y=t_y; y<t_y+it_h; y++)
    {
        for(int x=t_x; x<t_x+it_w; x++)
        {
            Tile *t = get(x, y);
            if(t->getType() != TT_Normal || t->containsResource())
            {
                return false;
            }
        }
    }

    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {

        if((*vit)->contains(t_x*Tile::TILE_WIDTH, t_y*Tile::TILE_HEIGHT))
        {
            return false;
        }
    }

    building->setPoint(t_x * Tile::TILE_WIDTH, t_y * Tile::TILE_HEIGHT);
    buildings.push_back(building);

    return true;
}

void GameMap::forcePlaceBuilding(MBuilding *building, int t_x, int t_y)
{
    float t_w = (float)(building->getWidth()) / (float)Tile::TILE_WIDTH;
    float t_h = (float)(building->getHeight()) / (float)Tile::TILE_HEIGHT;

    int it_w = (int)ceil(t_w);
    int it_h = (int)ceil(t_h);

    for(int y=t_y; y<t_y+it_h; y++)
    {
        for(int x=t_x; x<t_x+it_w; x++)
        {
            Tile *t = get(x, y);
            if(t->getType() != TT_Normal)
            {
                t->setTextureId(defaultTexture);
                t->setType(TT_Normal);
            }

            t->cleanResource();
        }
    }

    building->setPoint(t_x * Tile::TILE_WIDTH, t_y * Tile::TILE_HEIGHT);
    buildings.push_back(building);
}

int GameMap::getTextureCount()
{
    return textures.size();
}

int GameMap::addTexture(std::string name)
{
    int index = textures.size();
    textures.push_back(name);
    return index;
}

std::string GameMap::getDefaultTexture(void)
{
    return textures[defaultTexture];
}

int GameMap::getDefaultTextureId(void)
{
    return defaultTexture;
}

void GameMap::load(std::string input, AssetManager *asset)
{
    std::ifstream in (input.c_str(), std::ifstream::in | std::ifstream::binary);

    STRData::MapHeader header;

    in.read((char*)&header, sizeof(header));

    width = header.width;
    height = header.height;
    seed = header.seed;

    for(int i=0; i<header.nbTextures; i++)
    {
        STRData::TileTexture tt;
        in.read((char*)&tt, sizeof(STRData::TileTexture));
        std::string tname = tt.name;
        textures.push_back(tname);
    }

    initTiles();

    STRData::TileInfo ti;

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            in.read((char*)&ti, sizeof(STRData::TileInfo));
            Tile *t = get(x, y);
            t->setType(static_cast<TileType>(ti.type));
        }
    }

    STRData::ResourceMarker rmark;

    in.read((char*)&rmark, sizeof(STRData::ResourceMarker));

    STRData::ResourceInfo ri;

    for(int i=0; i<rmark.count; i++)
    {
        in.read((char*)&ri, sizeof(STRData::ResourceInfo));
        Tile *t = get(ri.x, ri.y);
        if(ri.type == RT_METAL)
        {
            t->setResource(asset->getMetalIdentity()->create());
        }
        else if(ri.type == RT_GAZ)
        {
            t->setResource(asset->getGazIdentity()->create());
        }

        t->getResource()->setAmount(ri.amount);
    }

    in.close();
}

void GameMap::save(std::string output)
{
    std::ofstream out (output.c_str(), std::ofstream::out | std::ofstream::binary);


    //writing map header
    STRData::MapHeader header;
    header.width = width;
    header.height = height;
    header.seed = seed;
    header.nbTextures = textures.size();

    out.write(reinterpret_cast<char*>(&header), sizeof(STRData::MapHeader));


    //texture list
    auto vit(textures.begin()), vend(textures.end());
    for(;vit!=vend;++vit)
    {
        STRData::TileTexture tt;
        tt.name[(*vit).size()] = 0;
        std::memcpy(&tt.name, (*vit).c_str(), (*vit).size());

        out.write(reinterpret_cast<char*>(&tt), sizeof(STRData::TileTexture));
    }

    STRData::TileInfo ti;

    std::vector<StiGame::Point> resPts;

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = get(x, y);
            ti.type = t->getType();
            ti.texture_id = t->getTextureId();
            out.write(reinterpret_cast<char*>(&ti), sizeof(STRData::TileInfo));

            if(t->containsResource())
            {
                resPts.push_back(StiGame::Point(x, y));
            }
        }
    }

    STRData::ResourceMarker rmark;
    rmark.count = resPts.size();
    out.write(reinterpret_cast<char*>(&rmark), sizeof(STRData::ResourceMarker));

    auto lit(resPts.begin()), lend(resPts.end());
    for(;lit!=lend;++lit)
    {
        Tile *t = get((*lit).getX(), (*lit).getY());
        Resource *r = t->getResource();

        STRData::ResourceInfo ri;
        ri.x = (*lit).getX();
        ri.y = (*lit).getY();
        ri.amount = r->getAmount();
        ri.type = r->getType();

        out.write(reinterpret_cast<char*>(&ri), sizeof(STRData::ResourceInfo));
    }

    out.close();


}


std::string GameMap::getTexture(int id)
{
    return textures[id];
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
    pmap->setDefaultTextureId(defaultTexture);

    auto tit(textures.begin()), tend(textures.end());
    for(;tit!=tend;++tit)
    {
        pmap->addTexture((*tit));
    }

    for(int y=0; y<height; y++)
    {
            for(int x=0; x<width; x++)
            {
                Tile *t = get(x, y)->clone();
                pmap->addTile(y, t);
            }
    }

    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getOwner()->getId() == playerId)
        {
            pmap->addBuilding((*vit));
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

