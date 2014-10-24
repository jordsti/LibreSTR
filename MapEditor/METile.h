#ifndef METILE_H
#define METILE_H
#include "MapData.h"
class METile
{
public:
    METile();
    virtual ~METile();

    STRData::TileType type;
    std::string texture;
};

#endif // METILE_H
