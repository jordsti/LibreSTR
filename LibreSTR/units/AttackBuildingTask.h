#ifndef ATTACKBUILDINGTASK_H
#define ATTACKBUILDINGTASK_H
#include "MoveTask.h"

class AttackBuildingTask :
        public MoveTask
{
public:
    AttackBuildingTask(MGroundUnit *m_unit, GameMap *m_map, MBuilding *m_target);
    virtual ~AttackBuildingTask();

protected:
    void doStep(void);
    MBuilding *target;
};

#endif // ATTACKBUILDINGTASK_H
