#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <BaseGameState.h>
#include <Surface.h>

#include "SpriteLibrary.h"
#include "TopHud.h"
#include "MiniMap.h"
#include "GameObject.h"
#include "RadialMenu.h"
#include "SelectionEventListener.h"

class GameState :
    public StiGame::BaseGameState,
    public StiGame::KeyEventListener,
    public StiGame::MouseButtonEventListener,
    public StiGame::MouseMotionEventListener,
    public StiGame::Gui::SelectionEventListener
{
    public:
        static const int VIEW_MOVE_DX;
        static const int VIEW_MOVE_DY;
        static const int VIEW_RECT_ZONE;

        GameState(AssetManager *m_assets);
        virtual ~GameState();
        void quit(void);
        void unload(void);
        void onStart(void);
        void onPaint(SDL_Renderer *renderer);
        void handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args);
        void handleEvent(StiGame::MouseButtonEventThrower *src, StiGame::MouseButtonEventArgs *args);
        void handleEvent(StiGame::MouseMotionEventThrower *src, StiGame::MouseMotionEventArgs *args);
        void handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *args);
        void onResize(int m_width, int m_height);

        void setViewPoint(int t_x, int t_y);
        void moveViewPoint(int dx, int dy);

        AssetManager* getAssets(void);
        MiniMap* getMiniMap(void);

    protected:
        void loadSprites(void);
        void drawBaseMap(void);
        void tickMouseViewMovement(void);
        void renderGui(SDL_Renderer *renderer);

        StiGame::SpriteLibrary *sprites;
        AssetManager *assets;
        PlayerMap *pmap; //temp
        GameObject *game;
    private:
        StiGame::MPoint mousePosition;
        int viewX;
        int viewY;
        StiGame::Gui::Label lblFps;
        TopHud *topHud;
        StiGame::Surface *baseMap;
        StiGame::Color background;
        StiGame::Color textColor;
        MiniMap *miniMap;

        RadialMenu baseMenu;

        //view rectangle for moving
        StiGame::Rectangle viewRectUp;
        StiGame::Rectangle viewRectDown;
        StiGame::Rectangle viewRectLeft;
        StiGame::Rectangle viewRectRight;
};

#endif // GAMESTATE_H
