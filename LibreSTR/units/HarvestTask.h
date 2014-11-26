#ifndef HARVESTTASK_H
#define HARVESTTASK_H

#include "MoveTask.h"
#include "MPlayer.h"

class HarvestTask :
        public MoveTask
{
public:
    HarvestTask(MGroundUnit *m_unit, MPlayer *m_player, int m_harvestSpeed, GameMap *m_map, StiGame::Point m_endPoint);
    virtual ~HarvestTask();

protected:
    void doStep(void);
    int harvestSpeed;

    MPlayer *player;
};

#endif // HARVESTTASK_H
