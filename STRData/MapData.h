#ifndef MAPDATA_H
#define MAPDATA_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace STRData
{

const int TEXTURE_NAME_LENGTH = 32;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;


enum ResourceType {
    RT_NOT_DEFINED = 0,
    RT_METAL = 1,
    RT_GAZ = 2
};

enum TileType {
    TT_Normal,
    TT_Water,
    TT_Block
};

struct MapHeader
{
    int width;
    int height;
    int seed;
    int nbTextures;
};

struct TileTexture {
    char name[TEXTURE_NAME_LENGTH];
};

struct TileInfo
{
    int type;
    int texture_id;
};

struct ResourceMarker
{
    int count;
};

struct ResourceInfo
{
    int x;
    int y;
    int amount;
    int type;
};

class MapData
{
public:
    MapData();
    MapData(int width, int height);
    virtual ~MapData();
    std::vector< std::vector< TileInfo > > tiles;
    std::vector< TileTexture > textures;
    std::vector< ResourceInfo > resources;

    void load(std::string input);
    void save(std::string output);

    int getWidth(void);
    int getHeight(void);
    int getSeed(void);

    TileInfo* getTileInfo(int t_x, int t_y);
    TileTexture* getTexture(int index);
    ResourceInfo* getResource(int index);

    int getTextureCount(void);
    int getResourceCount(void);

    int addTexture(std::string m_texture);
    int addResource(ResourceInfo& resourceInfo);

protected:
    void initTiles(void);
    int width;
    int height;
    int seed;
};

}

#endif
