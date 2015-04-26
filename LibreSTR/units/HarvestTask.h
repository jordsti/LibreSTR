#ifndef HARVESTTASK_H
#define HARVESTTASK_H

#include "MoveTask.h"
#include "MPlayer.h"

enum HarvestState {
    HS_Harvesting,
    HS_MovingToResource,
    HS_MovingToDepot
};

class HarvestTask :
        public MoveTask
{
public:
    HarvestTask(MGroundUnit *m_unit, MPlayer *m_player, GameMap *m_map, StiGame::Point m_endPoint);
    virtual ~HarvestTask();

    static Building* findNearestDepot(GameMap *m_map, GroundUnit *m_unit);

protected:
    void doStep(void);
    int harvestSpeed;
    int harvestRange;
    int currentResources;
    int resourcesLimit;
    HarvestState state;
    MPlayer *player;
    Building *depot;
    ResourceType resourceType;
    StiGame::MPoint resourcePoint;
};

#endif // HARVESTTASK_H
