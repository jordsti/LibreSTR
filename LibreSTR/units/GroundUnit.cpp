#include "GroundUnit.h"
#include <MathTK.h>
GroundUnit::GroundUnit(GroundUnitIdentity *m_identity, Player *m_owner)
    : Unit()
{
    type = UT_Ground;
    identity = m_identity;
    owner = m_owner;
    name = identity->getName();
    width = identity->getWidth();
    height = identity->getHeight();
    vision = identity->getVision();
    maxHealth = identity->getMaxHealth();
    currentHealth = identity->getMaxHealth();
    state = GUS_Idle;
}

GroundUnit::~GroundUnit()
{
}

int GroundUnit::getSize(void)
{
    return (int)StiGame::Math::TK::Pythagoras(width, height);
}

GroundUnitState GroundUnit::getState(void)
{
    return state;
}

bool GroundUnit::contains(int p_x, int p_y)
{

}

int GroundUnit::getVision(void)
{
    return vision;
}

std::string GroundUnit::getSpriteName(void)
{
    return identity->getSprite(owner->getPlayerColor(), state);
}

GroundUnitIdentity* GroundUnit::getIdentity(void)
{
    return identity;
}
