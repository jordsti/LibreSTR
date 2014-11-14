#include "CreateUnitEmitter.h"
#include "CreateUnitJob.h"

CreateUnitEmitter::CreateUnitEmitter(MPlayer *m_owner, GroundUnitIdentity *m_identity, GameMap *m_gameMap)
{
    owner = m_owner;
    identity = m_identity;
    gameMap = m_gameMap;
}

CreateUnitEmitter::~CreateUnitEmitter()
{

}

Job* CreateUnitEmitter::emitJob(void)
{
    CreateUnitJob *job = new CreateUnitJob(owner, identity, gameMap);
}
