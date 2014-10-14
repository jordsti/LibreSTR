#ifndef MGROUNDUNIT_H
#define MGROUNDUNIT_H
#include "GroundUnit.h"
class MGroundUnit :
        public GroundUnit
{
public:
    MGroundUnit(GroundUnitIdentity *m_identity, Player *m_owner);
    virtual ~MGroundUnit();

};

#endif // MGROUNDUNIT_H
