#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseGameState.h>
#include <Surface.h>

#include "SpriteLibrary.h"
#include "GameMap.h"
#include "AssetManager.h"
#include "TopHud.h"

class GameState :
    public StiGame::BaseGameState,
    public StiGame::KeyEventListener
{
    public:
        GameState(AssetManager *m_assets, GameMap *m_gameMap);
        virtual ~GameState();
        void quit(void);
        void onStart(void);
        void onPaint(SDL_Renderer *renderer);
        void handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args);
        void onResize(int m_width, int m_height);
    protected:
        void loadSprites(void);
        void drawBaseMap(void);

        GameMap *gameMap;
        StiGame::SpriteLibrary *sprites;
        AssetManager *assets;
    private:
        int viewX;
        int viewY;
        TopHud topHud;
        StiGame::Surface *baseMap;
        StiGame::Color background;
};

#endif // GAMESTATE_H
