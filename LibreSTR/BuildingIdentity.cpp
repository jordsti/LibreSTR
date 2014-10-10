#include "BuildingIdentity.h"
#include "Building.h"
#include <VarFile.h>
BuildingIdentity::BuildingIdentity(std::string id_file)
{
    StiGame::VarFile vf (id_file);
    vf.read();

    name = vf.getValue("name");
    spriteName = vf.getValue("spriteName");
    maxHealth = vf.getInt("maxHealth");
    width = vf.getInt("width");
    height = vf.getInt("height");
    metalCost = vf.getInt("metalCost");
    gazCost = vf.getInt("gazCost");
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

std::string BuildingIdentity::getName(void)
{
    return name;
}

std::string BuildingIdentity::getSpriteName(void)
{
    return spriteName;
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

Building* BuildingIdentity::create(void)
{
    return new Building(this);
}
