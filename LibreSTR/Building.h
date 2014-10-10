#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"

class Building :
        public Unit
{
public:
    Building();
    virtual ~Building();
    bool contains(int p_x, int p_y);
};

#endif // BUILDING_H
