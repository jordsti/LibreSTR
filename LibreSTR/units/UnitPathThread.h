#ifndef UNITPATHTHREAD_H
#define UNITPATHTHREAD_H
#include "UnitPath.h"
#include <SGThread.h>
class MoveTask;

enum UnitThreadStatus {
    UTS_Running,
    UTS_Complete
};

class UnitPathThread
{
public:
    UnitPathThread(MoveTask *m_moveTask, StiGame::Point m_start, StiGame::Point m_end);
    virtual ~UnitPathThread();
    UnitThreadStatus status;
    StiGame::Point start;
    StiGame::Point end;
    UnitPath *path;
    MoveTask *moveTask;
    StiGame::Thread *thread;
};


int FindPath(void *data_ptr);

#endif // UNITPATHTHREAD_H
