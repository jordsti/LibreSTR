#include "Building.h"

Building::Building() : Unit()
{
    type = UT_Building;
    name = "Generec Building";
    spriteName = "building";
    width = 64;
    height = 64;
}

bool Building::contains(int p_x, int p_y)
{
    return (p_x >= x &&
            p_x <= x + width &&
            p_y >= y &&
            p_y <= height);
}

Building::~Building()
{
}
