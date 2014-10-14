#include "GroundUnitIdentity.h"

#include <VarFile.h>
#include "MGroundUnit.h"

GroundUnitIdentity::GroundUnitIdentity(std::string vf_file)
{
    StiGame::VarFile vf (vf_file);
    vf.read();
}

GroundUnitIdentity::~GroundUnitIdentity()
{
}

MGroundUnit* GroundUnitIdentity::create(Player *owner)
{
    return new MGroundUnit(this, owner);
}

std::string GroundUnitIdentity::getName(void)
{
    return name;
}

int GroundUnitIdentity::getMetalCost(void)
{
    return metalCost;
}

int GroundUnitIdentity::getGazCost(void)
{
    return gazCost;
}

int GroundUnitIdentity::getAttackRange(void)
{
    return attackRange;
}

int GroundUnitIdentity::getWidth(void)
{
    return width;
}

int GroundUnitIdentity::getHeight(void)
{
    return height;
}

int GroundUnitIdentity::getVision(void)
{
    return vision;
}

int GroundUnitIdentity::getMaxHealth(void)
{
    return maxHealth;
}

int GroundUnitIdentity::getMovementSpeed(void)
{
    return movemenSpeed;
}
