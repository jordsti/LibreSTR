#include "Task.h"

Task::Task(std::string m_name)
{
    name = m_name;
    stepSize = 0;
    stepCount = 0;
    terminated = false;
    msLeft = 0;
    caption = "None";
}


Task::~Task()
{

}


std::string Task::getCaption()
{
    return caption;
}

bool Task::isTerminated(void)
{
    return terminated;
}

void Task::tick(int ms)
{
    if(terminated)
    {
        return;
    }

    if(msLeft > 0)
    {
        ms += msLeft;
        msLeft = 0;
    }

    if(ms >= stepSize)
    {
        int step = ms / stepSize;
        msLeft = ms % stepSize;
        for(int i=0; i<step; i++)
        {
            doStep();
            stepCount++;
        }
    }
}

std::string Task::getName(void)
{
    return name;
}

int Task::getStepCount(void)
{
    return stepCount;
}

int Task::getStepSize(void)
{
    return stepSize;
}
