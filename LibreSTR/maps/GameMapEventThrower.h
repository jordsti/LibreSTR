#ifndef GAMEMAPEVENTTHROWER_H
#define GAMEMAPEVENTTHROWER_H
#include <vector>
#include "GameMapEvent.h"

class GameMapEventListener;

class GameMapEventThrower
{
public:
    GameMapEventThrower();
    virtual ~GameMapEventThrower();

    virtual void publish(GameMapEvent *event);
    virtual void subscribe(GameMapEventListener *listener);

private:
    std::vector<GameMapEventListener*> listeners;

};

#endif // GAMEMAPEVENTTHROWER_H
