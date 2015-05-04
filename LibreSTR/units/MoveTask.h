#ifndef MOVETASK_H
#define MOVETASK_H
#include "Task.h"
#include "GameMap.h"
#include "UnitPath.h"
#include "UnitPathThread.h"

class MoveTask :
        public Task
{
public:
    MoveTask(MGroundUnit *m_unit, GameMap *m_map, StiGame::Point m_endPoint);
    virtual ~MoveTask();
    StiGame::Point *getEndPoint(void);
    ITileMap *getMap(void);
    void setUnitPath(UnitPath *m_path);
    void clearThread(void);
protected:
    void endPointCorrection(void);
    void setEndPoint(StiGame::Point m_endPoint);

    virtual void doStep(void);
    MGroundUnit *unit;
    GameMap *map;
private:
    UnitPathThread *thread;
    bool waiting;
    StiGame::MPoint endPoint;
    UnitPath *path;
};

#endif // MOVETASK_H
