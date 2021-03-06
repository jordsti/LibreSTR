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

    auto uit(units.begin()), uend(units.end());
    for(;uit!=uend;++uit)
    {
        delete (*uit);
    }

    auto bit(buildings.begin()), bend(buildings.end());
    for(;bit!=bend;++bit)
    {
        delete (*bit);
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

MGroundUnit* GameMap::getGroundUnitById(int id)
{
    auto vit(units.begin()), vend(units.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == id)
        {
            return (*vit);
        }
    }

    return nullptr;
}

int GameMap::getBuildingsCount(void)
{
    return buildings.size();
}

MBuilding* GameMap::getBuilding(int index)
{
    return buildings[index];
}

MBuilding* GameMap::getBuildingById(int id)
{
    MBuilding *b = nullptr;
    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == id)
        {
            return (*vit);
        }
    }

    return b;
}

void GameMap::tickUnits(int ms)
{

    //removing dead units atm
    //todo
    //in the future, put a dead sprite for each unit

    std::vector<MBuilding*> _buildings;

    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        (*vit)->tickJob(ms);

        if(!(*vit)->isDead())
        {
            _buildings.push_back((*vit));
        }
        else
        {
            deleteQueue.push_back((*vit));
            GameMapEvent gme (GMET_BuildingKilled, (*vit));
            publish(&gme);
        }

    }

    buildings.clear();
    buildings = _buildings;

    std::vector<MGroundUnit*> _groundUnits;

    auto vit2(units.begin()), vend2(units.end());
    for(;vit2!=vend2;++vit2)
    {
        (*vit2)->tickTask(ms);

        if(!(*vit2)->isDead())
        {
            _groundUnits.push_back((*vit2));
        }
        else
        {
            deleteQueue.push_back((*vit2));
            //units killed
            GameMapEvent gme (GMET_GroundUnitKilled, (*vit2));
            publish(&gme);
        }
    }

    units.clear();
    units = _groundUnits;

}

bool GameMap::placeGroundUnit(MGroundUnit *unit, int pt_x, int pt_y, bool updatePlayerMap)
{
    unit->setPoint(pt_x, pt_y);
    StiGame::Point mpt = unit->middle();

    //need to check if tile doesn't contains a ressource or is a block

    StiGame::Point tilePt (mpt.getX() / Tile::TILE_WIDTH, mpt.getY() / Tile::TILE_HEIGHT);

    Tile *tile = get(tilePt.getX(), tilePt.getY());

    if(tile->containsResource() || tile->getType() == TT_Block)
    {
        return false;
    }

    //not inside a building
    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->contains(mpt.getX(), mpt.getY()))
        {
            return false;
        }
    }

    //no collision with exsiting unit

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

    //placing this into player map
    if(playerMaps.size() > 0 && updatePlayerMap)
    {
        PlayerMap *pmap = playerMaps[unit->getOwner()->getId()];
        if(!pmap->containsGroundUnit(unit))
        {
            pmap->addGroundUnit(unit);
        }
    }


    return true;
}

void GameMap::placeGroundUnitAroundPoint(MGroundUnit *unit, int pt_x, int pt_y, bool updatePlayerMap)
{
    StiGame::Point tilePt(pt_x / Tile::TILE_WIDTH, pt_y / Tile::TILE_HEIGHT);
    bool pointFound = false;

    StiGame::MPoint pt;

    int u_w = unit->getWidth() / Tile::TILE_WIDTH;
    int u_h = unit->getHeight() / Tile::TILE_HEIGHT;

    if(unit->getWidth() % Tile::TILE_WIDTH > 0)
    {
        u_w++;
    }

    if(unit->getHeight() % Tile::TILE_HEIGHT > 0)
    {
        u_h++;
    }

    int step = 1;
    while(!pointFound)
    {
        int c_step = step / 2;

        int d_x = (rand() % step) - c_step;
        int d_y = (rand() % step) - c_step;

        pt.setPoint((tilePt.getX() + d_x), (tilePt.getY() + d_y));

        for(int i=0; i<u_w; i++)
        {
            for(int j=0; j<u_h; j++)
            {
                Tile *t = get(i+pt.getX(), j+pt.getY());
                if(!t->containsResource() && t->getType() == TT_Normal)
                {
                    //unit collision
                    StiGame::Rectangle uRect (pt.getX() * Tile::TILE_WIDTH, pt.getY() * Tile::TILE_HEIGHT, unit->getWidth(), unit->getHeight());
                    if(!unitCollision(&uRect))
                    {
                        pointFound = true;
                    }
                }
            }
        }

        step++;

        //quick hot fix

        if(step > 1000)
        {
            break;
        }
    }

    unit->setPoint(pt.getX() * Tile::TILE_WIDTH, pt.getY() * Tile::TILE_HEIGHT);
    units.push_back(unit);

    //placing this into player map
    if(playerMaps.size() > 0 && updatePlayerMap)
    {
        PlayerMap *pmap = playerMaps[unit->getOwner()->getId()];
        if(!pmap->containsGroundUnit(unit))
        {
            pmap->addGroundUnit(unit);
        }
    }

}

StiGame::Point GameMap::findNearestResource(StiGame::Point tilePt, int t_w, int t_h, ResourceType r_type)
{
    int s_x = tilePt.getX() - t_w / 2;
    int s_y = tilePt.getY() - t_h / 2;

    for(int i=0; i<t_w; i++)
    {
        int t_x = tilePt.getX() + i;
        for(int j=0; j<t_h; j++)
        {
            int t_y = tilePt.getY() + j;

            Tile *t = get(t_x, t_y);
            if(t->containsResource())
            {
                if(t->getResource()->getType() == r_type)
                {
                    return StiGame::Point(t_x, t_y);
                }
            }

        }
    }

    return StiGame::Point(0, 0);

}

bool GameMap::unitCollision(StiGame::Rectangle *rect)
{
    auto uit(units.begin()), uend(units.end());
    for(;uit!=uend;++uit)
    {
        GroundUnit *gu = (*uit);
        StiGame::Point mpt = gu->middle();

        if(rect->contains(&mpt) || rect->contains(gu))
        {
            return true;
        }
    }

    auto bit(buildings.begin()), bend(buildings.end());
    for(;bit!=bend;++bit)
    {
        Building *bu = (*bit);
        StiGame::Point mpt = bu->middle();
        if(rect->contains(&mpt) || rect->contains(bu))
        {
            return true;
        }
    }

    return false;
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

PlayerMap* GameMap::generatePlayerMap(Player *m_player)
{
    int playerId = m_player->getId();
    PlayerMap *pmap = new PlayerMap(width, height, m_player);
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

    auto vit2(units.begin()), vend2(units.end());
    for(;vit2!=vend2;++vit2)
    {
        if((*vit2)->getOwner()->getId() == playerId)
        {
            pmap->addGroundUnit((*vit2));
        }
    }

    playerMaps.insert(std::make_pair(playerId, pmap));

    return pmap;

}

bool GameMap::buildingsContains(StiGame::Point *pt)
{
    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->contains(pt->getX(), pt->getY()))
        {
            return true;
        }
    }

    return false;
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

Tile* GameMap::get(StiGame::Point& pt)
{
    int x = pt.getX();
    int y = pt.getY();
    return get(x, y);
}
