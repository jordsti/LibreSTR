#include "PlayerMap.h"

PlayerMap::PlayerMap(int m_width, int m_height, Player *m_player)
{
    //ctor
    width = m_width;
    height = m_height;
    defaultTexture = 0;
    player = m_player;
    initRows();
}

PlayerMap::~PlayerMap()
{
    //dtor
    //todo
    auto vit(tiles.begin()), vend(tiles.end());
    for(;vit!=vend;++vit)
    {
        auto vit2((*vit).begin()), vend2((*vit).end());
        for(;vit2!=vend2;++vit2)
        {
            delete (*vit2);
        }
    }
}

Player* PlayerMap::getPlayer(void)
{
    return player;
}

bool PlayerMap::isBuildingLocationValid(BuildingIdentity *buildingId, StiGame::Point *pt)
{
    int t_w = buildingId->getWidth() / Tile::TILE_WIDTH;
    int t_h = buildingId->getHeight() / Tile::TILE_HEIGHT;

    if(buildingId->getWidth() %  Tile::TILE_WIDTH > 0)
    {
        t_w++;
    }

    if(buildingId->getHeight() % Tile::TILE_HEIGHT > 0)
    {
        t_h++;
    }

    //assuming that the point is tile position
    for(int i=0; i<t_w; i++)
    {
        for(int j=0; j<t_h; j++)
        {
            int t_x = i + ( pt->getX() / Tile::TILE_WIDTH );
            int t_y = j + ( pt->getY() / Tile::TILE_HEIGHT );

            if(t_x < width &&
                t_y < height &&
                t_x >= 0 &&
                t_y >=0 )
            {
                Tile *t = get(t_x, t_y);

                if(t->containsResource() || t->getType() != TT_Normal)
                {
                    //invalid resource or rock
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    //another building on it
    auto bit(buildings.begin()), bend(buildings.end());
    for(;bit!=bend;++bit)
    {
        Building *b = (*bit);
        StiGame::Point mpt (pt->getX()+ (buildingId->getWidth()/2),
                            pt->getY() + (buildingId->getHeight()/2) );
        if(b->contains(pt) || b->contains(&mpt))
        {
            return false;
        }

    }

    //todo
    //to unit
    //deplacement

    return true;

}

bool PlayerMap::isPointVisible(StiGame::Point *pt)
{
    auto uit(units.begin()), uend(units.end());
    for(;uit!=uend;++uit)
    {
        GroundUnit *gu = (*uit);
        StiGame::Point mpt = gu->middle();
        double dist = mpt.distanceWith(pt);
        if(dist <= gu->getVision())
        {
            return true;
        }

    }

    auto bit(buildings.begin()), bend(buildings.end());
    for(;bit!=bend;++bit)
    {
        Building *bu = (*bit);
        StiGame::Point mpt = bu->middle();
        double dist = mpt.distanceWith(pt);
        if(dist <= bu->getVision())
        {
            return true;
        }
    }

    return false;
}

void PlayerMap::cleanUnits(void)
{
    auto bit(buildings.begin()), bend(buildings.end());
    std::vector<Building*> tmpBuildings;
    for(;bit!=bend;++bit)
    {
        if((*bit)->getOwner() == player)
        {
            tmpBuildings.push_back((*bit));
        }

    }

    buildings.clear();

    auto tit(tmpBuildings.begin()), tend(tmpBuildings.end());
    for(;tit!=tend;++tit)
    {
        buildings.push_back((*tit));
    }


    auto uit(units.begin()), uend(units.end());
    std::vector<GroundUnit*> toKeeps;
    for(;uit!=uend;++uit)
    {
        if((*uit)->getOwner() == player)
        {
            toKeeps.push_back((*uit));
        }
    }

    units.clear();

    auto kit(toKeeps.begin()), kend(toKeeps.end());
    for(;kit!=kend;++kit)
    {
        units.push_back((*kit));
    }
}

bool PlayerMap::containsBuilding(Building *building)
{
    auto vit(buildings.begin()), vend(buildings.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == building->getId())
        {
            return true;
        }
    }

    return false;
}

bool PlayerMap::containsGroundUnit(GroundUnit *unit)
{
    auto vit(units.begin()), vend(units.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->getId() == unit->getId())
        {
            return true;
        }
    }

    return false;
}

int PlayerMap::getGroundUnitsCount(void)
{
    return units.size();
}

GroundUnit* PlayerMap::getGroundUnit(int index)
{
    return units[index];
}

void PlayerMap::addGroundUnit(GroundUnit *m_unit)
{
    units.push_back(m_unit);
}

int PlayerMap::getBuildingsCount(void)
{
    return buildings.size();
}

Building* PlayerMap::getBuilding(int index)
{
    //todo
    return buildings[index];
}

void PlayerMap::addBuilding(Building *m_building)
{
    buildings.push_back(m_building);
}

int PlayerMap::getWidth(void)
{
    return width;
}

int PlayerMap::getHeight(void)
{
    return height;
}

int PlayerMap::getDefaultTextureId(void)
{
    return defaultTexture;
}

void PlayerMap::setDefaultTextureId(int m_defaultTexture)
{
    defaultTexture = m_defaultTexture;
}

std::string PlayerMap::getDefaultTexture(void)
{
    return textures[defaultTexture];
}

std::string PlayerMap::getTexture(int id)
{
    return textures[id];
}

int PlayerMap::getTextureCount(void)
{
    return textures.size();
}

void PlayerMap::addTexture(std::string m_texture)
{
    textures.push_back(m_texture);
}

void PlayerMap::addTile(int row, Tile *tile)
{
    if(row < height)
    {
        tiles[row].push_back(tile);
        tileRefs.push_back(tile);

        if(tile->containsResource())
        {
            resRefs.push_back(tile->getResource());
        }
    }
}

Resource* PlayerMap::getResource(int resId)
{
    auto lit(resRefs.begin()), lend(resRefs.end());
    for(;lit!=lend;++lit)
    {
        if((*lit)->getId() == resId)
        {
            return (*lit);
        }
    }

    return nullptr;
}

Tile* PlayerMap::get(int tileId)
{
    auto lit(tileRefs.begin()), lend(tileRefs.end());
    for(;lit!=lend;++lit)
    {
        if( (*lit)->getId() == tileId )
        {
            return (*lit);
        }
    }

    return nullptr;
}

StiGame::Point PlayerMap::getPosition(Tile *tile)
{
    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = tiles[y][x];
            if(t == tile || t->getId() == tile->getId())
            {
                return StiGame::Point(x, y);
            }
        }
    }

    return StiGame::Point(-1, -1);
}

Tile* PlayerMap::get(int x, int y)
{
    return tiles[y][x];
}

void PlayerMap::initRows(void)
{
    for(int r=0; r<height; r++)
    {
        std::vector<Tile*> row;
        tiles.push_back(row);
    }
}
