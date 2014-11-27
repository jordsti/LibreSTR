#ifndef GROUNDUNITSPRITEMANAGER_H
#define GROUNDUNITSPRITEMANAGER_H

#include "DirectionSpriteLibrary.h"
#include "GroundUnit.h"

struct GroundUnitSprite {
    GroundUnit *unit;
    StiGame::ClonedDirectionSprite *clone;
};

class GroundUnitSpriteManager
{
public:
    GroundUnitSpriteManager();
    virtual ~GroundUnitSpriteManager();

    void setLibrary(StiGame::DirectionSpriteLibrary *m_library);



    StiGame::ClonedDirectionSprite* getUnitSprite(GroundUnit *gUnit);

    void tick(void);


private:
    std::vector< GroundUnitSprite > sprites;
    StiGame::DirectionSpriteLibrary *library;
};

#endif // GROUNDUNITSPRITEMANAGER_H
