#include "GroundUnitSpriteManager.h"

GroundUnitSpriteManager::GroundUnitSpriteManager()
{
    library = nullptr;
}

GroundUnitSpriteManager::~GroundUnitSpriteManager()
{

}

void GroundUnitSpriteManager::setLibrary(StiGame::DirectionSpriteLibrary *m_library)
{
    library = m_library;
}



StiGame::ClonedDirectionSprite* GroundUnitSpriteManager::getUnitSprite(GroundUnit *gUnit)
{
    auto vit(sprites.begin()), vend(sprites.end());
    for(;vit!=vend;++vit)
    {
        if( (*vit).unit == gUnit || (*vit).unit->getId() == gUnit->getId() )
        {
            StiGame::ClonedDirectionSprite *clone = (*vit).clone;

            if(clone->getDirection() != gUnit->getDirection())
            {
                clone->setDirection(gUnit->getDirection());
            }

            return clone;
        }
    }

    //need to clone a new sprite
    std::string spr_name =  gUnit->getSpriteName();
    StiGame::ClonedDirectionSprite *clone = library->clone(spr_name);

    GroundUnitSprite _sprite;
    _sprite.clone = clone;
    _sprite.unit = gUnit;

    if(clone->getDirection() != gUnit->getDirection())
    {
        clone->setDirection(gUnit->getDirection());
    }

    sprites.push_back(_sprite);

    return clone;
}

void GroundUnitSpriteManager::tick(void)
{
    auto vit(sprites.begin()), vend(sprites.end());
    for(;vit!=vend;++vit)
    {
        GroundUnit *unit = (*vit).unit;
        StiGame::ClonedDirectionSprite *clone = (*vit).clone;

        if(unit->isWorking())
        {
            clone->tick();
        }

        //else image is not changing
    }
}
