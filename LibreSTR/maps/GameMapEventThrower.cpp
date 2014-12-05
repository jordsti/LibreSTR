#include "GameMapEventThrower.h"
#include "GameMapEventListener.h"

GameMapEventThrower::GameMapEventThrower()
{

}

GameMapEventThrower::~GameMapEventThrower()
{

}

void GameMapEventThrower::publish(GameMapEvent *event)
{
    auto vit(listeners.begin()), vend(listeners.end());
    for(;vit!=vend;++vit)
    {
        (*vit)->handleEvent(this, event);
    }
}

void GameMapEventThrower::subscribe(GameMapEventListener *listener)
{
    listeners.push_back(listener);
}
