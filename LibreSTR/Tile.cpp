#include "Tile.h"

const int Tile::TILE_WIDTH = 32;
const int Tile::TILE_HEIGHT = 32;

Tile::Tile()
{
    //ctor
    type = TT_Normal;
    texture = "";
}

Tile::Tile(TileType m_type, std::string m_texture)
{
    //ctor
    type = m_type;
    texture = m_texture;
}

Tile::~Tile()
{
    //dtor
}

TileType Tile::getType(void)
{
    return type;
}

std::string Tile::getTexture(void)
{
    return texture;
}


void Tile::setType(TileType m_type)
{
    type = m_type;
}

void Tile::setTexture(std::string m_texture)
{
    texture = m_texture;
}
