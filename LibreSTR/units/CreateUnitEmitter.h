#ifndef CREATEUNITEMITTER_H
#define CREATEUNITEMITTER_H

#include "JobEmitter.h"
#include "MPlayer.h"
#include "GroundUnitIdentity.h"
#include "GameMap.h"

class CreateUnitEmitter :
        public JobEmitter
{
public:
    CreateUnitEmitter(MPlayer *m_owner, GroundUnitIdentity *m_identity, GameMap *m_gameMap);
    virtual ~CreateUnitEmitter();

    Job* emitJob(void);

private:
    MPlayer *owner;
    GroundUnitIdentity *identity;
    GameMap *gameMap;

};

#endif // CREATEUNITEMITTER_H
