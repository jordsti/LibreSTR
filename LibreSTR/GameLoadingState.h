#ifndef GAMELOADINGSTATE_H
#define GAMELOADINGSTATE_H

#include <LoadingState.h>

class GameLoadingState :
        public LoadingState
{
public:
    GameLoadingState(LoadableObject *m_object);
    virtual ~GameLoadingState();
};

#endif // GAMELOADINGSTATE_H
