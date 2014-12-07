#ifndef GAMEOBJECTLISTENER_H
#define GAMEOBJECTLISTENER_H

#include "Player.h"

class GameObjectListener
{
public:
    GameObjectListener();
    virtual ~GameObjectListener();

    virtual void handlePlayerDefeat(Player *defeated) = 0;
    virtual void handlePlayerVictory(Player *winner) = 0;
};

#endif // GAMEOBJECTLISTENER_H
