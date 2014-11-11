#include "GroundUnitIdentity.h"

#include <VarFile.h>
#include "MGroundUnit.h"

GroundUnitIdentity::GroundUnitIdentity(std::string vf_file)
{
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

    std::map<PlayerColor, std::string> map1;
    sprites.insert(std::make_pair(GUS_Idle, map1));
    std::map<PlayerColor, std::string> map2;
    sprites.insert(std::make_pair(GUS_Attacking, map2));
    std::map<PlayerColor, std::string> map3;
    sprites.insert(std::make_pair(GUS_Working, map3));

    std::string idle_blue = vf.getValue("sprite_idle_blue");
    std::string idle_red = vf.getValue("sprite_idle_red");

    sprites[GUS_Idle].insert(std::make_pair(PC_Blue, idle_blue));
    sprites[GUS_Idle].insert(std::make_pair(PC_Red, idle_red));
}

GroundUnitIdentity::~GroundUnitIdentity()
{
}

MGroundUnit* GroundUnitIdentity::create(Player *owner)
{
    return new MGroundUnit(this, owner);
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
