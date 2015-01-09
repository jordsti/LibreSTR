#include "LoadingState.h"

LoadingState::LoadingState(LoadableObject *m_object)
{
    object = m_object;
    tick = 0;
}


LoadingState::~LoadingState()
{

}

void LoadingState::onPaint(SDL_Renderer *renderer)
{
    //todo
    //progress bar and all the shizzle!

    if(tick == 0)
    {
        //first paint
    }
    else if(!object->isComplete())
    {
        //loading
        object->load();
        //and painting
    }
    else
    {
        //completed
        object->onCompletition();
    }

    tick++;

}

void LoadingState::onStart(void)
{
    running = true;
}
