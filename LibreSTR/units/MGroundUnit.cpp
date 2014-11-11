#include "MGroundUnit.h"

MGroundUnit::MGroundUnit(GroundUnitIdentity *m_identity, Player *m_owner) : GroundUnit(m_identity, m_owner)
{

}

MGroundUnit::~MGroundUnit()
{

}

void MGroundUnit::setState(GroundUnitState m_state)
{
    state = m_state;
}
