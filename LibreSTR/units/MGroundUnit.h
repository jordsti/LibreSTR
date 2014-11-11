#ifndef MGROUNDUNIT_H
#define MGROUNDUNIT_H
#include "GroundUnit.h"
class MGroundUnit :
        public GroundUnit
{
public:
    MGroundUnit(GroundUnitIdentity *m_identity, Player *m_owner);
    virtual ~MGroundUnit();

    void setState(GroundUnitState m_state);
};

#endif // MGROUNDUNIT_H
