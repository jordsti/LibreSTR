#ifndef JOB_H
#define JOB_H
#include <string>
class Job
{
public:
    virtual ~Job();

    void tick(int ms);
    bool isCompleted(void);
    std::string getName(void);
    void cancel(void);
    int getId(void);
    bool isCancelled(void);
    int getTimeElapsed(void);
    int getTimeNeeded(void);

protected:
    Job(std::string m_name);

    virtual void onComplete(void);
    virtual void onStart(void);
    virtual void onCancel(void);

    int timeNeeded;
    bool cancelable;
private:
    bool cancelled;
    std::string name;
    bool completed;
    int timeElapsed;
    int _id;
    static int currentId;
    static int GenerateId(void);
};

#endif // JOB_H
