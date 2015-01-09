#ifndef LOADABLEOBJECT_H
#define LOADABLEOBJECT_H

#include <string>

class LoadableObject
{
public:
    LoadableObject();
    virtual ~LoadableObject();

    bool isComplete(void);

    std::string getCaption(void);
    int getMaxProgress(void);
    int getCurrentProgress(void);


    virtual void load(void) = 0;
    virtual void onCompletition(void) = 0;
protected:
    std::string caption;
    int maxProgress;
    int currentProgress;
    bool complete;
};

#endif // LOADABLEOBJECT_H
