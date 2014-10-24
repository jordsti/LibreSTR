#include "MapData.h"
#include <iostream>
#include <cstring>

namespace STRData
{

MapData::MapData()
{
    width = 0;
    height = 0;
}

MapData::MapData(int m_width, int m_height)
{
    width = m_width;
    height = m_height;

    for(int y=0; y<height; y++)
    {
        std::vector< TileInfo > row;
        for(int x=0; x<width; x++)
        {
            TileInfo ti;
            ti.texture_id =0;
            ti.type = TT_Normal;
            row.push_back(ti);
        }
        tiles.push_back(row);
    }
}

MapData::~MapData()
{

}

void MapData::load(std::string input)
{
    std::ifstream in (input.c_str(), std::ifstream::in | std::ifstream::binary);

    MapHeader header;

    in.read((char*)&header, sizeof(header));

    width = header.width;
    height = header.height;
    seed = header.seed;
    initTiles();

    for(int i=0; i<header.nbTextures; i++)
    {
        TileTexture tt;
        textures.push_back(tt);
    }

    initTiles();

    TileInfo ti;

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            tiles[y].push_back(ti);
        }
    }

    ResourceMarker rmark;

    in.read((char*)&rmark, sizeof(ResourceMarker));

    ResourceInfo ri;

    for(int i=0; i<rmark.count; i++)
    {
        in.read((char*)&ri, sizeof(ResourceInfo));

        resources.push_back(ri);
    }

    in.close();
}

void MapData::save(std::string output)
{
    std::ofstream out (output.c_str(), std::ofstream::out | std::ofstream::binary);

    //writing map header
    MapHeader header;
    header.width = width;
    header.height = height;
    header.seed = seed;
    header.nbTextures = textures.size();

    out.write(reinterpret_cast<char*>(&header), sizeof(MapHeader));


    //texture list
    auto vit(textures.begin()), vend(textures.end());
    for(;vit!=vend;++vit)
    {
        out.write(reinterpret_cast<char*>(&(*vit)), sizeof(TileTexture));
    }

    auto rit(tiles.begin()), rend(tiles.end());
    for(;rit!=rend;++rit)
    {
        auto cit((*rit).begin()), cend((*rit).end());
        for(;cit!=cend;++cit)
        {
            out.write(reinterpret_cast<char*>(&(*cit)), sizeof(TileInfo));
        }
    }

    ResourceMarker rmark;
    rmark.count = resources.size();
    out.write(reinterpret_cast<char*>(&rmark), sizeof(ResourceMarker));

    auto lit(resources.begin()), lend(resources.end());
    for(;lit!=lend;++lit)
    {
        out.write(reinterpret_cast<char*>(&(*lit)), sizeof(ResourceInfo));
    }

    out.close();
}

TileInfo* MapData::getTileInfo(int t_x, int t_y)
{
    return &(tiles[t_y][t_x]);
}

TileTexture* MapData::getTexture(int index)
{
    return &(textures[index]);
}

ResourceInfo* MapData::getResource(int index)
{
    return &(resources[index]);
}

int MapData::getTextureCount(void)
{
    return textures.size();
}

int MapData::getResourceCount(void)
{
    return resources.size();
}

int MapData::addTexture(std::string m_texture)
{
    TileTexture tt;
    tt.name[m_texture.size()] = 0;
    std::memcpy(&tt.name, m_texture.c_str(), m_texture.size());

    int index = textures.size();

    textures.push_back(tt);
    return index;
}

int MapData::addResource(ResourceInfo& resourceInfo)
{
    int index = resources.size();
    resources.push_back(resourceInfo);
    return index;
}

int MapData::getWidth(void)
{
    return width;
}

int MapData::getHeight(void)
{
    return height;
}

int MapData::getSeed(void)
{
    return seed;
}

void MapData::initTiles(void)
{
    for(int y=0; y<height; y++)
    {
        std::vector<TileInfo> row;
        tiles.push_back(row);
    }
}

}
