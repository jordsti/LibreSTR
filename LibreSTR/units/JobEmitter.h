#ifndef JOBEMITTER_H
#define JOBEMITTER_H

#include "Job.h"
class JobEmitter
{
public:
    JobEmitter();
    virtual ~JobEmitter();

    virtual Job* emitJob(void);
};

#endif // JOBEMITTER_H
