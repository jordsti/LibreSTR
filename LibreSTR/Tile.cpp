#include "Tile.h"

const int Tile::TILE_WIDTH = 32;
const int Tile::TILE_HEIGHT = 32;

int Tile::_currentId = 0;

int Tile::GetCurrentId(void)
{
    int id = _currentId;

    _currentId++;

    return id;
}

Tile::Tile()
{
    //ctor
    type = TT_Normal;
    texture = "";
    resource = nullptr;
    _id = GetCurrentId();
}

Tile::Tile(TileType m_type, std::string m_texture)
{
    //ctor
    type = m_type;
    texture = m_texture;
    resource = nullptr;
    _id = GetCurrentId();
}

Tile::Tile(TileType m_type, std::string m_texture, int m_id)
{
    //ctor
    //for clone purpose

    type = m_type;
    texture = m_texture;
    _id = m_id;
    resource = nullptr;
}

Tile* Tile::clone(void)
{
    Tile *cTile = new Tile(type, texture, _id);

    if(containsResource())
    {
        cTile->setResource(resource->clone());
    }
}

Tile::~Tile()
{
    //dtor
    if(containsResource())
    {
        delete resource;
    }
}

int Tile::getId(void)
{
    return _id;
}

TileType Tile::getType(void)
{
    return type;
}

std::string Tile::getTexture(void)
{
    return texture;
}

IResource* Tile::getResource(void)
{
    return resource;
}

bool Tile::containsResource(void)
{
    return resource != nullptr;
}


void Tile::setType(TileType m_type)
{
    type = m_type;
}

void Tile::setTexture(std::string m_texture)
{
    texture = m_texture;
}

void Tile::setResource(IResource *m_resource)
{
    resource = m_resource;
}
