#ifndef BUILDINGSPRITE_H
#define BUILDINGSPRITE_H
#include "SpriteLibrary.h"
#include "UnitSprite.h"
#include "Building.h"
#include <vector>

class BuildingSprite :
        public UnitSprite
{
public:
    BuildingSprite(Building *m_building, StiGame::SpriteLibrary *m_library);
    virtual ~BuildingSprite();

    void render(void);
    Unit* getUnit(void);
protected:
    StiGame::SpriteLibrary *library;
    Building *building;
    std::map<std::string, StiGame::ClonedSprite> sprites;
};

#endif // BUILDINGSPRITE_H
