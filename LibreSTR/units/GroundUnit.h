#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Unit.h"
#include "GroundUnitIdentity.h"

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
protected:

    GroundUnitIdentity *identity;
};

#endif // GROUNDUNIT_H
