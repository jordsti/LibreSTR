#ifndef JOBEMITTER_H
#define JOBEMITTER_H

#include "Job.h"

class Building;

class JobEmitter
{
public:
    JobEmitter();
    virtual ~JobEmitter();

    virtual Job* emitJob(Building *building) = 0;
};

#endif // JOBEMITTER_H
