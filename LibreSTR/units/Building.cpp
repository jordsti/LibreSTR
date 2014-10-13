#include "Building.h"

Building::Building(BuildingIdentity *m_identity, Player *m_owner) : Unit()
{
    owner = m_owner;
    _identity = m_identity;
    state = BS_Placed;

    type = UT_Building;
    width = _identity->getWidth();
    height = _identity->getHeight();
    maxHealth = _identity->getMaxHealth(); //cuz its placed
    currentHealth = 1;
    name = _identity->getName();
}

int Building::getCurrentHealth()
{
    return currentHealth;
}

BuildingState Building::getState(void)
{
    return state;
}


BuildingIdentity* Building::getIdentity(void)
{
    return _identity;
}

bool Building::contains(int p_x, int p_y)
{
    return (p_x >= x &&
            p_x <= x + width &&
            p_y >= y &&
            p_y <= height);
}

int Building::getMetalCost(void)
{
    return _identity->getMetalCost();
}

int Building::getGazCost(void)
{
    return _identity->getGazCost();
}

int Building::getVision(void)
{
    return _identity->getVision();
}

std::string Building::getSpriteName()
{
    if(state == BS_Placed)
    {
        return _identity->getPlacedSprite();
    }
    else if(state == BS_Construction)
    {
        return _identity->getConstructSprite(owner->getPlayerColor());
    }
    else if(state == BS_Builded)
    {
        return _identity->getSpriteName(owner->getPlayerColor());
    }

    return "";
}

Building::~Building()
{
}
