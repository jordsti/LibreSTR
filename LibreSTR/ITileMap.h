#ifndef ITILEMAP_H
#define ITILEMAP_H

#include "Tile.h"

class ITileMap
{
public:
    virtual int getWidth(void) = 0;
    virtual int getHeight(void) = 0;
    virtual Tile* get(int t_x, int t_y) = 0;
    virtual std::string getTexture(int id) = 0;
    virtual int getDefaultTextureId(void) = 0;
    virtual std::string getDefaultTexture(void) = 0;
    virtual int getTextureCount(void) = 0;
protected:
    ITileMap();
    virtual ~ITileMap();

};

#endif // ITILEMAP_H
