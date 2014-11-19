#include "CreateUnitJob.h"

CreateUnitJob::CreateUnitJob(MPlayer *m_player, Building *m_srcBuilding, GroundUnitIdentity *m_identity, GameMap *m_gameMap) :
    Job("Create Unit")
{
    timeNeeded = m_identity->getProductionTime();
    player = m_player;
    srcBuilding = m_srcBuilding;
    identity = m_identity;
    gameMap = m_gameMap;
}

CreateUnitJob::~CreateUnitJob()
{

}

void CreateUnitJob::onComplete(void)
{
    //placing the unit here

    int pt_x = 0;
    int pt_y = 0;

    MGroundUnit *unit = identity->create(player);

    pt_x = srcBuilding->getX() + srcBuilding->getWidth();
    pt_y = srcBuilding->getY() + srcBuilding->getHeight();

    while(!gameMap->placeGroundUnit(unit, pt_x, pt_y))
    {
        pt_x += Tile::TILE_WIDTH;
        pt_y += Tile::TILE_HEIGHT;
    }

}

void CreateUnitJob::onCancel(void)
{
    int metalCount = player->getMetalCount() + identity->getMetalCost();
    int gazCount = player->getGazCount() + identity->getGazCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
}

void CreateUnitJob::onStart(void)
{
    int metalCount = player->getMetalCount() - identity->getMetalCost();
    int gazCount = player->getGazCount() - identity->getGazCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
}
