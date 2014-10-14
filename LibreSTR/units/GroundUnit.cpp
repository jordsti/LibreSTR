#include "GroundUnit.h"

GroundUnit::GroundUnit(GroundUnitIdentity *m_identity, Player *m_owner)
    : Unit()
{
    identity = m_identity;
    owner = m_owner;
    name = identity->getName();
    width = identity->getWidth();
    height = identity->getHeight();
    vision = identity->getVision();

}

GroundUnit::~GroundUnit()
{
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
    //todo
    return "";
}

GroundUnitIdentity* GroundUnit::getIdentity(void)
{
    return identity;
}
