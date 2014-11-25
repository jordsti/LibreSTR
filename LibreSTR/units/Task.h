#ifndef TASK_H
#define TASK_H

#include <string>

/*
 * Task is like Job for GroundUnit
 * Only the current task is running, there is no queue
 */

class Task
{
public:
    virtual ~Task();
    bool isTerminated(void);
    void tick(int ms);
    int getStepCount(void);
    int getStepSize(void);
    std::string getName(void);
    std::string getCaption(void);
protected:
    Task(std::string m_name);
    virtual void doStep(void) = 0;
    int stepCount;
    int stepSize;
    bool terminated;
    std::string name;
    std::string caption;
private:
    int msLeft;
};

#endif // TASK_H
