#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseGameState.h>
#include <Surface.h>

#include "SpriteLibrary.h"
#include "GameMap.h"
#include "AssetManager.h"
#include "TopHud.h"
#include "MiniMap.h"

class GameState :
    public StiGame::BaseGameState,
    public StiGame::KeyEventListener,
    public StiGame::MouseButtonEventListener
{
    public:
        GameState(AssetManager *m_assets, GameMap *m_gameMap);
        virtual ~GameState();
        void quit(void);
        void unload(void);
        void onStart(void);
        void onPaint(SDL_Renderer *renderer);
        void handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args);
        void handleEvent(StiGame::MouseButtonEventThrower *src, StiGame::MouseButtonEventArgs *args);
        void onResize(int m_width, int m_height);

        void setViewPoint(int t_x, int t_y);

        AssetManager* getAssets(void);

    protected:
        void loadSprites(void);
        void drawBaseMap(void);

        GameMap *gameMap;
        StiGame::SpriteLibrary *sprites;
        AssetManager *assets;
        PlayerMap *pmap; //temp
    private:
        int viewX;
        int viewY;
        TopHud *topHud;
        StiGame::Surface *baseMap;
        StiGame::Color background;
        MiniMap *miniMap;
};

#endif // GAMESTATE_H
