#include "MBuilding.h"

MBuilding::MBuilding(BuildingIdentity *m_identity, Player *m_owner) :
    Building(m_identity, m_owner)
{

}

MBuilding::~MBuilding()
{
}

void MBuilding::setState(BuildingState m_state)
{
    state = m_state;
}

void MBuilding::setCurrentHealth(int m_currentHealth)
{
    currentHealth = m_currentHealth;
}
