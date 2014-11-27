#ifndef BUILDTASK_H
#define BUILDTASK_H

#include "MoveTask.h"

class BuildTask :
        public MoveTask
{
public:
    BuildTask(MGroundUnit *m_unit, int m_buildSpeed, MBuilding *m_building, GameMap *m_map, StiGame::Point m_endPoint);
    virtual ~BuildTask();

protected:
    void doStep(void);
private:
    MBuilding *building;
    int buildSpeed;
};

#endif // BUILDTASK_H
