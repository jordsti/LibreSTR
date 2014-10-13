#include "UnitSprite.h"

UnitSprite::UnitSprite(int m_unitId)
{
    unitId = m_unitId;
}

UnitSprite::~UnitSprite()
{

}

int UnitSprite::getUnitId(void)
{
    return unitId;
}
