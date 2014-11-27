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

    void pushTask(Task *m_task);

    void setDirection(StiGame::SDirection m_direction);

    void tickTask(int ms);
};

#endif // MGROUNDUNIT_H
