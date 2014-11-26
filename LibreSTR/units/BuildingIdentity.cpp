#include "BuildingIdentity.h"
#include "MBuilding.h"
#include <VarFile.h>

BuildingIdentity::BuildingIdentity(BuildingType m_buildingType, std::string id_file)
{
    StiGame::VarFile vf (id_file);
    vf.read();

    name = vf.getValue("name");
    maxHealth = vf.getInt("maxHealth");
    width = vf.getInt("width");
    height = vf.getInt("height");
    metalCost = vf.getInt("metalCost");
    gazCost = vf.getInt("gazCost");
    vision = vf.getInt("vision");
    placedSprite = vf.getValue("placedSprite");
    icon = vf.getValue("icon");

    constructSprites.insert(make_pair(PC_Blue, vf.getValue("sprite_construct_blue")));
    constructSprites.insert(make_pair(PC_Red, vf.getValue("sprite_construct_red")));

    sprites.insert(make_pair(PC_Blue, vf.getValue("sprite_blue")));
    sprites.insert(make_pair(PC_Red, vf.getValue("sprite_red")));

    buildingType = m_buildingType;
}

std::string BuildingIdentity::getIcon(void)
{
    return icon;
}

BuildingType BuildingIdentity::getBuildingType(void)
{
    return buildingType;
}

std::string BuildingIdentity::getPlacedSprite(void)
{
    return placedSprite;
}

int BuildingIdentity::getMetalCost(void)
{
    return metalCost;
}

int BuildingIdentity::getGazCost(void)
{
    return gazCost;
}

int BuildingIdentity::getMaxHealth(void)
{
    return maxHealth;
}

int BuildingIdentity::getVision()
{
    return vision;
}

std::string BuildingIdentity::getName(void)
{
    return name;
}

std::string BuildingIdentity::getSpriteName(PlayerColor playerColor)
{
    return sprites[playerColor];
}

std::string BuildingIdentity::getConstructSprite(PlayerColor playerColor)
{
    return constructSprites[playerColor];
}

int BuildingIdentity::getWidth(void)
{
    return width;
}

int BuildingIdentity::getHeight(void)
{
    return height;
}

BuildingIdentity::~BuildingIdentity()
{

}

MBuilding* BuildingIdentity::create(Player *owner)
{
    //Here all resource cost ARE ALREADY REMOVED FROM THE PLAYER!
    return new MBuilding(this, owner);
}
