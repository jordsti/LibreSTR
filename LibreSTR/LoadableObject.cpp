#include "LoadableObject.h"

LoadableObject::LoadableObject()
{
    complete = false;
    caption = "Loading...";
    maxProgress = 1;
    currentProgress = 0;
}


LoadableObject::~LoadableObject()
{

}

bool LoadableObject::isComplete(void)
{
    return complete;
}

std::string LoadableObject::getCaption(void)
{
    return caption;
}

int LoadableObject::getMaxProgress(void)
{
    return maxProgress;
}

int LoadableObject::getCurrentProgress(void)
{
    return currentProgress;
}
