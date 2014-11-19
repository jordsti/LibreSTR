#include "MBuilding.h"

MBuilding::MBuilding(BuildingIdentity *m_identity, Player *m_owner) :
    Building(m_identity, m_owner)
{

}

MBuilding::~MBuilding()
{
}

void MBuilding::setState(BuildingState m_state)
{
    state = m_state;
}

void MBuilding::setCurrentHealth(int m_currentHealth)
{
    currentHealth = m_currentHealth;
}

void MBuilding::addEmitter(JobEmitter *m_emitter)
{
    emitters.push_back(m_emitter);
}

void MBuilding::emitJob(int index)
{
    if(index < emitters.size())
    {
        JobEmitter *emitter = emitters[index];

        Job *newJob = emitter->emitJob(this);
        newJob->start();
        if(currentJob == nullptr)
        {
            currentJob = newJob;
        }
        else
        {
            jobsQueue.push(newJob);
        }

    }
}

void MBuilding::tickJob(int ms)
{
    if(currentJob != nullptr)
    {
        currentJob->tick(ms);
        if(currentJob->isCompleted() || currentJob->isCancelled())
        {
            //todo
            //delete the job here
            currentJob = nullptr;

            //takin next item in the queue
            if(jobsQueue.size() > 0)
            {
                currentJob = jobsQueue.front();

                jobsQueue.pop();
            }
        }
    }
}
