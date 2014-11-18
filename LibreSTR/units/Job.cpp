#include "Job.h"
int Job::currentId = 0;

int Job::GenerateId()
{
    currentId++;
    return currentId;
}

Job::Job(std::string m_name)
{
    name = m_name;
    completed = false;
    timeNeeded = 0;
    timeElapsed = 0;
    cancelable = true;
    cancelled = false;
    _id = GenerateId();
}

Job::~Job()
{

}

void Job::start(void)
{
    if(timeElapsed == 0)
    {
        onStart();
    }
}

void Job::cancel(void)
{
    if(cancelable)
    {
        cancelled = true;
        onCancel();
    }
}

int Job::getTimeElapsed(void)
{
    return timeElapsed;
}

int Job::getTimeNeeded(void)
{
    return timeNeeded;
}

void Job::tick(int ms)
{
    if(cancelled && cancelable)
    {
        return;
    }

    timeElapsed += ms;
    if(timeElapsed >= timeNeeded)
    {
        //completed
        completed = true;
        onComplete();
    }
}

int Job::getId(void)
{
    return _id;
}

bool Job::isCompleted(void)
{
    return completed;
}

bool Job::isCancelled(void)
{
    return cancelled;
}

std::string Job::getName(void)
{
    return name;
}

void Job::onComplete(void)
{
    //must override this
}

void Job::onStart(void)
{
    //must override this
}

void Job::onCancel(void)
{
    //must override this
}
