#include "PlayerMap.h"

PlayerMap::PlayerMap(int m_width, int m_height)
{
    //ctor
    width = m_width;
    height = m_height;
    defaultTexture = 0;
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