#include "CreateUnitJob.h"

CreateUnitJob::CreateUnitJob(MPlayer *m_player, GroundUnitIdentity *m_identity, GameMap *m_gameMap) :
    Job("Create Unit")
{
    timeNeeded = m_identity->getProductionTime();
    player = m_player;
    identity = m_identity;
    gameMap = m_gameMap;
}

CreateUnitJob::~CreateUnitJob()
{

}

void CreateUnitJob::onComplete(void)
{
    //placing the unit here
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
