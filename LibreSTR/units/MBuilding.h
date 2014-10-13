#ifndef MBUILDING_H
#define MBUILDING_H

#include "Building.h"

class MBuilding :
        public Building
{
public:
    MBuilding(BuildingIdentity *m_identity, Player *m_owner);
    virtual ~MBuilding();

    void setState(BuildingState m_state);
    void setCurrentHealth(int m_currentHealth);
};

#endif // MBUILDING_H
