#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseGameState.h>
#include <Surface.h>

#include "SpriteLibrary.h"
#include "GameMap.h"

class GameState :
    public StiGame::BaseGameState
{
    public:
        GameState(GameMap *m_gameMap);
        virtual ~GameState();
        void quit(void);
        void onStart(void);
    protected:
        void loadSprites(void);
        void drawBaseMap(void);

        GameMap *gameMap;
        StiGame::SpriteLibrary *sprites;

    private:
        StiGame::Surface *baseMap;
        StiGame::Color background;
};

#endif // GAMESTATE_H
