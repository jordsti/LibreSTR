#include "Building.h"

Building::Building(BuildingIdentity *m_identity) : Unit()
{
    _identity = m_identity;
    type = UT_Building;
    /*name = "Generec Building";
    spriteName = "building";
    width = 64;
    height = 64;*/
    width = _identity->getWidth();
    height = _identity->getHeight();
    maxHealth = _identity->getMaxHealth();
    currentHealth = _identity->getMaxHealth();
    name = _identity->getName();
    spriteName = _identity->getSpriteName();
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
