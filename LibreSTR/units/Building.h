#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"
#include "BuildingIdentity.h"

enum BuildingState {
    BS_Placed,
    BS_Construction,
    BS_Builded
};

class Building :
        public Unit
{
public:
    Building(BuildingIdentity *m_identity, Player *m_owner);
    virtual ~Building();
    bool contains(int p_x, int p_y);
    BuildingState getState(void);
    int getMetalCost(void);
    int getGazCost(void);
    int getVision(void);
    int getCurrentHealth(void);
    std::string getSpriteName(void);
    BuildingIdentity* getIdentity(void);
protected:
    BuildingState state;
    BuildingIdentity *_identity;

};

#endif // BUILDING_H