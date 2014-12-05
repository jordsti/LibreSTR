#ifndef ATTACKGROUNDUNITTASK_H
#define ATTACKGROUNDUNITTASK_H

#include "MoveTask.h"

class AttackGroundUnitTask :
        public MoveTask
{
public:
    AttackGroundUnitTask(MGroundUnit *m_unit, GameMap *m_map, MGroundUnit *m_target);
    virtual ~AttackGroundUnitTask();
protected:
    void doStep(void);

    MGroundUnit *target;

};

#endif // ATTACKTASK_H
