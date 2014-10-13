#include "BuildingSprite.h"

using namespace StiGame;

//TODO
//override StiGame:Sprite move

BuildingSprite::BuildingSprite(Building *m_building, StiGame::SpriteLibrary *m_library)
    : UnitSprite(m_building->getId())
{
    building = m_building;
    library = m_library;

    //pushing sprite
    std::string placed = building->getIdentity()->getPlacedSprite();
    ClonedSprite sprPlaced (m_library->getSprite(placed));

    std::string construct = building->getIdentity()->getConstructSprite(building->getOwner()->getPlayerColor());
    ClonedSprite sprConstruct (m_library->getSprite(construct));

    std::string builded = building->getIdentity()->getSpriteName(building->getOwner()->getPlayerColor());
    ClonedSprite sprBuilded (m_library->getSprite(builded));

    sprites.insert(make_pair(placed, sprPlaced));
    sprites.insert(make_pair(construct, sprConstruct));
    sprites.insert(make_pair(builded, sprBuilded));

}

BuildingSprite::~BuildingSprite()
{

}

void BuildingSprite::render(void)
{
    //render code !
    std::string current = building->getSpriteName();
    if(current.size() > 0)
    {
        sprites[current].render();
    }

}

Unit* BuildingSprite::getUnit(void)
{

}
