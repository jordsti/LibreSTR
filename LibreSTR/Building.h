#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"
#include "BuildingIdentity.h"

class Building :
        public Unit
{
public:
    Building(BuildingIdentity *m_identity);
    virtual ~Building();
    bool contains(int p_x, int p_y);
private:
    BuildingIdentity *_identity;

};

#endif // BUILDING_H
