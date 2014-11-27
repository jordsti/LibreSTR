#include "MGroundUnit.h"

MGroundUnit::MGroundUnit(GroundUnitIdentity *m_identity, Player *m_owner) : GroundUnit(m_identity, m_owner)
{

}

MGroundUnit::~MGroundUnit()
{

}

void MGroundUnit::setState(GroundUnitState m_state)
{
    state = m_state;
}


void MGroundUnit::pushTask(Task *m_task)
{
    if(currentTask != nullptr)
    {
        delete currentTask;
        currentTask = m_task;
    }
    else
    {
        currentTask = m_task;
    }
}

void MGroundUnit::tickTask(int ms)
{
    if(currentTask != nullptr)
    {
        currentTask->tick(ms);

        if(currentTask->isTerminated())
        {
            delete currentTask;
            currentTask = nullptr;
        }
    }
}


void MGroundUnit::setDirection(StiGame::SDirection m_direction)
{
    direction = m_direction;
}
