#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#include <BaseGameState.h>
#include <LoadableObject.h>

class LoadingState :
        public StiGame::BaseGameState
{
public:
    LoadingState(LoadableObject *m_object);
    virtual ~LoadingState();

    void onPaint(SDL_Renderer *renderer);
    void onStart(void);

    LoadableObject* getObject(void);

protected:
    LoadableObject *object;
    int tick;
};

#endif // LOADINGSTATE_H
