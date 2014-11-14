#ifndef CREATEUNITJOB_H
#define CREATEUNITJOB_H

#include "Job.h"
#include "MPlayer.h"
#include "GroundUnitIdentity.h"
#include "GameMap.h"

class CreateUnitJob :
        public Job
{
public:
    CreateUnitJob(MPlayer *m_player, GroundUnitIdentity *identity, GameMap *m_gampeMap);
    virtual ~CreateUnitJob();

protected:
    void onComplete(void);
    void onCancel(void);
    void onStart(void);

private:
    MPlayer *player;
    GroundUnitIdentity *identity;
    GameMap *gameMap;
};

#endif // CREATEUNITJOB_H
