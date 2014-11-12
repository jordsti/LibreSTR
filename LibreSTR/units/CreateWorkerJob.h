#ifndef CREATEWORKERJOB_H
#define CREATEWORKERJOB_H

#include "Job.h"
#include "MPlayer.h"
#include "GroundUnitIdentity.h"

class CreateWorkerJob :
        public Job
{
public:
    CreateWorkerJob(MPlayer *m_player, GroundUnitIdentity *workerIdentity);
    virtual ~CreateWorkerJob();

protected:
    void onComplete(void);
    void onCancel(void);
    void onStart(void);

private:
    MPlayer *player;
    GroundUnitIdentity *workerIdentity;
};

#endif // CREATEWORKERJOB_H
