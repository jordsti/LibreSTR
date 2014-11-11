#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Unit.h"
#include "GroundUnitIdentity.h"
#include <map>

enum GroundUnitState : int {
    GUS_Idle,
    GUS_Attacking,
    GUS_Working
};

class GroundUnit :
        public Unit
{
public:
    GroundUnit(GroundUnitIdentity *m_identity, Player *m_owner);
    ~GroundUnit();
    bool contains(int p_x, int p_y);
    int getVision(void);
    std::string getSpriteName(void);
    GroundUnitIdentity* getIdentity(void);
    int getSize(void);
    GroundUnitState getState(void);

protected:
    GroundUnitIdentity *identity;
    GroundUnitState state;
};

#endif // GROUNDUNIT_H
