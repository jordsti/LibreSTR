#include "CreateWorkerJob.h"

CreateWorkerJob::CreateWorkerJob(MPlayer *m_player, GroundUnitIdentity *m_workerIdentity) :
    Job("Create Worker")
{
    timeNeeded = workerIdentity->getProductionTime();
    player = m_player;
    workerIdentity = m_workerIdentity;
}

CreateWorkerJob::~CreateWorkerJob()
{

}

void CreateWorkerJob::onComplete(void)
{
    //placing the unit here
}

void CreateWorkerJob::onCancel(void)
{
    int metalCount = player->getMetalCount() + workerIdentity->getMetalCost();
    int gazCount = player->getGazCount() + workerIdentity->getGazCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
}

void CreateWorkerJob::onStart(void)
{
    int metalCount = player->getMetalCount() - workerIdentity->getMetalCost();
    int gazCount = player->getGazCount() - workerIdentity->getGazCost();
    player->setMetalCount(metalCount);
    player->setGazCount(gazCount);
}
