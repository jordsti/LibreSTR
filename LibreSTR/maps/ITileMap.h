#ifndef ITILEMAP_H
#define ITILEMAP_H

#include "Tile.h"
#include "Building.h"
#include "GroundUnit.h"

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

    virtual int getBuildingsCount(void) = 0;
    virtual Building* getBuilding(int index) = 0;

    virtual int getGroundUnitsCount(void) = 0;
    virtual GroundUnit* getGroundUnit(int index) = 0;

protected:
    ITileMap();
    virtual ~ITileMap();

};

#endif // ITILEMAP_H
