#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"
#include "BuildingIdentity.h"
#include "JobEmitter.h"
#include <vector>
#include <queue>

enum BuildingState : int {
    BS_Placed,
    BS_Construction,
    BS_Builded
};

enum BuildingType : int {
    BT_Base,
    BT_Barrack,
    BT_House
};

class Building :
        public Unit
{
public:
    Building(BuildingIdentity *m_identity, Player *m_owner);
    virtual ~Building();
    BuildingState getState(void);
    int getMetalCost(void);
    int getGazCost(void);
    int getVision(void);
    int getCurrentHealth(void);
    std::string getSpriteName(void);
    BuildingIdentity* getIdentity(void);

    int getJobEmittersCount(void);
    JobEmitter* getJobEmitter(int index);

    Job* getCurrentJob(void);

    BuildingType getBuildingType(void);

    int getPopulationCapacity(void);

protected:
    std::vector<JobEmitter*> emitters;
    std::queue<Job*> jobsQueue;

    Job *currentJob;

    BuildingState state;
    BuildingIdentity *_identity;

};

#endif // BUILDING_H
