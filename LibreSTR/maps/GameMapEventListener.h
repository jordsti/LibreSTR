#ifndef GAMEMAPEVENTLISTENER_H
#define GAMEMAPEVENTLISTENER_H

#include "GameMapEventThrower.h"

class GameMapEventListener
{
public:
    GameMapEventListener();
    virtual ~GameMapEventListener();

    virtual void handleEvent(GameMapEventThrower *src, GameMapEvent *event);
};

#endif // GAMEMAPEVENTLISTENER_H
