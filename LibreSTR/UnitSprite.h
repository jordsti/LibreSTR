#ifndef UNITSPRITE_H
#define UNITSPRITE_H
#include <Sprite.h>
#include "Unit.h"
class UnitSprite :
        StiGame::ISprite
{
public:
    virtual ~UnitSprite();
    virtual void render(void) = 0;
    virtual Unit* getUnit(void) = 0;
    int getUnitId(void);
protected:
    UnitSprite(int m_unitId);
    int unitId;

};

#endif // UNITSPRITE_H
