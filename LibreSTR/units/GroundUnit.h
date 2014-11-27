#ifndef GROUNDUNIT_H
#define GROUNDUNIT_H

#include "Unit.h"
#include "GroundUnitIdentity.h"
#include "Task.h"
#include <map>
#include "IDirectionSprite.h"

enum GroundUnitState : int {
    GUS_Attacking,
    GUS_Moving
};

class GroundUnit :
        public Unit
{
public:
    GroundUnit(GroundUnitIdentity *m_identity, Player *m_owner);
    ~GroundUnit();
    int getVision(void);
    std::string getSpriteName(void);
    GroundUnitIdentity* getIdentity(void);
    int getSize(void);
    GroundUnitState getState(void);

    Task* getTask(void);
    bool isWorking(void);

    StiGame::SDirection getDirection(void);

protected:
    StiGame::SDirection direction;
    GroundUnitIdentity *identity;
    GroundUnitState state;
    Task *currentTask;
};

#endif // GROUNDUNIT_H
