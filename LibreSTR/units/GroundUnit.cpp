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
    currentTask = nullptr;
    state = GUS_Moving;
    direction = StiGame::SD_UP;
}

GroundUnit::~GroundUnit()
{
}

StiGame::SDirection GroundUnit::getDirection(void)
{
    return direction;
}

int GroundUnit::getSize(void)
{
    return (int)StiGame::Math::TK::Pythagoras(width, height);
}

GroundUnitState GroundUnit::getState(void)
{
    return state;
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

Task* GroundUnit::getTask(void)
{
    return currentTask;
}

bool GroundUnit::isWorking(void)
{
    return currentTask != nullptr;
}

int GroundUnit::getAttackRange(void)
{
    return identity->getAttackRange();
}

int GroundUnit::getAttackDamage(void)
{
    return identity->getAttackDamage();
}
