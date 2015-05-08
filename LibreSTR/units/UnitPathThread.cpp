#include "UnitPathThread.h"
#include <SGThread.h>
#include "MoveTask.h"
UnitPathThread::UnitPathThread(MoveTask *m_moveTask, StiGame::Point m_start, StiGame::Point m_end)
{
    status = UTS_Running;
    path = nullptr;
    moveTask = m_moveTask;
    start = m_start;
    end = m_end;
    thread  = new StiGame::Thread(&FindPath, "UnitPathThread", this);
}


UnitPathThread::~UnitPathThread()
{
    delete thread;
}

int FindPath(void *data_ptr)
{
    UnitPathThread *th = static_cast<UnitPathThread*>(data_ptr);
    th->path = UnitPath::FindPath(th->start, th->end, th->moveTask->getMap());
    th->status = UTS_Complete;

    th->moveTask->setUnitPath(th->path);
    return 1;
}
