#include "GroundUnitIdentity.h"

#include <VarFile.h>
#include "MGroundUnit.h"

GroundUnitIdentity::GroundUnitIdentity(std::string vf_file)
{
    canHarvest = false;
    StiGame::VarFile vf (vf_file);
    vf.read();
    name = vf.getValue("name");
    metalCost = vf.getInt("metalCost");
    gazCost = vf.getInt("gazCost");
    attackRange = vf.getInt("attackRange");
    width = vf.getInt("width");
    height = vf.getInt("height");
    vision = vf.getInt("vision");
    maxHealth = vf.getInt("maxHealth");
    movementSpeed = vf.getInt("movementSpeed");
    movementStep = vf.getInt("movementStep");
    productionTime = vf.getInt("productionTime");

    icon = vf.getValue("icon");
    radialIcon = vf.getValue("radialIcon");
    radialHoverIcon = vf.getValue("radialHoverIcon");

    std::map<PlayerColor, std::string> map1;
    sprites.insert(std::make_pair(GUS_Moving, map1));
    std::map<PlayerColor, std::string> map2;
    sprites.insert(std::make_pair(GUS_Attacking, map2));

    std::string moving_blue = vf.getValue("sprite_moving_blue");
    std::string moving_red = vf.getValue("sprite_moving_red");

    sprites[GUS_Moving].insert(std::make_pair(PC_Blue, moving_blue));
    sprites[GUS_Moving].insert(std::make_pair(PC_Red, moving_red));

    canHarvest = vf.getBool("canHarvest");
    canBuild = vf.getBool("canBuild");
}

GroundUnitIdentity::~GroundUnitIdentity()
{
}

bool GroundUnitIdentity::isCanBuild()
{
    return canBuild;
}

int GroundUnitIdentity::getMovementStep()
{
    return movementStep;
}

bool GroundUnitIdentity::isCanHarvest(void)
{
    return canHarvest;
}

MGroundUnit* GroundUnitIdentity::create(Player *owner)
{
    return new MGroundUnit(this, owner);
}

std::string GroundUnitIdentity::getIcon(void)
{
    return icon;
}

std::string GroundUnitIdentity::getRadialIcon(void)
{
    return radialIcon;
}

std::string GroundUnitIdentity::getRadialHoverIcon(void)
{
    return radialHoverIcon;
}

std::string GroundUnitIdentity::getSprite(PlayerColor color, GroundUnitState state)
{
    return sprites[state][color];
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
    return movementSpeed;
}

int GroundUnitIdentity::getProductionTime(void)
{
    return productionTime;
}
