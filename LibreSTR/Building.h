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
    void setState(BuildingState m_state);
    int getMetalCost(void);
    int getGazCost(void);
    std::string getSpriteName(void);
    BuildingIdentity* getIdentity(void);
private:
    BuildingState state;
    BuildingIdentity *_identity;

};

#endif // BUILDING_H
