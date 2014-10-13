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
    textureId = 0;
    resource = nullptr;
    _id = GetCurrentId();
}

Tile::Tile(TileType m_type, int m_textureId)
{
    //ctor
    type = m_type;
    textureId = m_textureId;
    resource = nullptr;
    _id = GetCurrentId();
}

Tile::Tile(TileType m_type, int m_textureId, int m_id)
{
    //ctor
    //for clone purpose

    type = m_type;
    textureId = m_textureId;
    _id = m_id;
    resource = nullptr;
}

Tile* Tile::clone(void)
{
    Tile *cTile = new Tile(type, textureId, _id);

    if(containsResource())
    {
        cTile->setResource(resource->clone());
    }

    return cTile;
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

int Tile::getTextureId(void)
{
    return textureId;
}

Resource* Tile::getResource(void)
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

void Tile::setTextureId(int m_textureId)
{
    textureId = m_textureId;
}

void Tile::setResource(Resource *m_resource)
{
    resource = m_resource;
}

void Tile::cleanResource(void)
{
    delete resource;
    resource = nullptr;
}
