#ifndef MOVETASK_H
#define MOVETASK_H
#include "Task.h"
#include "GameMap.h"
class MoveTask :
        public Task
{
public:
    MoveTask(MGroundUnit *m_unit, GameMap *m_map, StiGame::Point m_endPoint);
    virtual ~MoveTask();

protected:
    void endPointCorrection(void);

    virtual void doStep(void);
    MGroundUnit *unit;
    GameMap *map;
    StiGame::Point endPoint;
};

#endif // MOVETASK_H
