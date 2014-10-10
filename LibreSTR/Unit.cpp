#include "Unit.h"

int Unit::_currentId = 0;

int Unit::getCurrentId(void)
{
    _currentId++;
    int id = _currentId;
}


Unit::Unit()
{
    _id = getCurrentId();
    name = "";
    type = UT_None;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    spriteName = "";
    currentHealth = 1;
    maxHealth = 1;
}


Unit::~Unit()
{

}

bool Unit::isDead(void)
{
    return (currentHealth == 0);
}


int Unit::getId(void)
{
    return _id;
}

std::string Unit::getName(void)
{
    return name;
}

std::string Unit::getSpriteName(void)
{
    return spriteName;
}

UnitType Unit::getType(void)
{
    return type;
}

int Unit::getMaxHealth(void)
{
    return maxHealth;
}

int Unit::getCurrentHealth(void)
{
    return currentHealth;
}
