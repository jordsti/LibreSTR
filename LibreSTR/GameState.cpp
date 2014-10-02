#include "GameState.h"
#include <Viewport.h>
#include <iostream>
#include "GameOverlay.h"
#include <OverlayGameAction.h>

using namespace StiGame;

GameState::GameState(AssetManager *m_assets, GameMap *m_gameMap) :
    BaseGameState()
{
    //ctor
    assets = m_assets;
    gameMap = m_gameMap;
    //gameMap = new GameMap();
    //gameMap->load("test.map", assets);
    background.setRGB(0, 0, 0);
    viewX = 0;
    viewY = 0;

}


GameState::~GameState()
{
    //dtor
}


void GameState::quit(void)
{
    running = false;
}

void GameState::onStart(void)
{
    sprites = new SpriteLibrary(viewport->getRenderer());
    loadSprites();
    drawBaseMap();

    GameOverlay *overlay = new GameOverlay();
    overlay->setState(this);
    KeyEventThrower::subscribe(overlay);

    setGameMenu(overlay);

    BaseGameAction *oaction = OverlayGameAction::GetDefaultOverlayGameAction(this);

    actions.push_back(oaction);

    KeyEventThrower::subscribe(this);

    running = true;
}

void GameState::handleEvent(KeyEventThrower *src, KeyEventArgs *args)
{
    if(args->getState() == KS_DOWN)
    {
        if(args->getKeyboardEvent()->keysym.sym == SDLK_UP)
        {
            if(viewY > 0)
            {
                viewY -= 16;
            }
        }
        else if(args->getKeyboardEvent()->keysym.sym == SDLK_DOWN)
        {
            if(viewY < (gameMap->getHeight() * Tile::TILE_HEIGHT) - height)
            {
                viewY += 16;
            }

        }
        else if(args->getKeyboardEvent()->keysym.sym == SDLK_LEFT)
        {
            if(viewX > 0)
            {
                viewX -= 16;
            }
        }
        else if(args->getKeyboardEvent()->keysym.sym == SDLK_RIGHT)
        {
            if(viewX < (gameMap->getWidth() * Tile::TILE_WIDTH) - width)
            {
                viewX += 16;
            }
        }
    }
}

void GameState::onPaint(SDL_Renderer *renderer)
{
    //todo move this plz !
    tickActions();



    SDL_Rect mapRect;
    SDL_Rect viewRect;

    mapRect.x = viewX;
    mapRect.y = viewY;
    mapRect.w = width;
    mapRect.h = height;

    viewRect.x = 0;
    viewRect.y = 0;
    viewRect.w = width;
    viewRect.h = height;


    Surface *buffer = new Surface(width, height);

    buffer->blit(baseMap, &mapRect, &viewRect);

    Texture tex (renderer, buffer);
    tex.renderCopy(&viewRect, &viewRect);

    BaseGameState::onPaint(renderer);
}

void GameState::drawBaseMap(void)
{
    baseMap = new Surface(gameMap->getWidth() * Tile::TILE_WIDTH, gameMap->getHeight() * Tile::TILE_WIDTH);
    baseMap->fill(&background);

    SDL_Rect dst;
    dst.w = Tile::TILE_WIDTH;
    dst.h = Tile::TILE_HEIGHT;

    Sprite *sprNormal = sprites->getSprite(assets->getTileNormal());
    Sprite *sprBlock = sprites->getSprite(assets->getTileBlock());

    Surface *sur;

    for(int y=0; y<gameMap->getHeight(); y++)
    {
        dst.y = y * Tile::TILE_HEIGHT;
        for(int x=0; x<gameMap->getWidth(); x++)
        {
            dst.x = x * Tile::TILE_WIDTH;

            Tile *t = gameMap->get(x, y);
            //draw grass on all tile
            sur = sprNormal->getCurrentSurface();

            baseMap->blit(sur, &dst);

            if(t->getType() == TT_Block)
            {
                sur = sprBlock->getCurrentSurface();

                baseMap->blit(sur, &dst);
                //draw a rock
            }

            if(t->containsResource())
            {
                IResource *rs = t->getResource();
                Sprite *sprRes = sprites->getSprite(rs->getTexture());

                sur = sprRes->getCurrentSurface();

                baseMap->blit(sur, &dst);
            }

        }
    }

}

void GameState::loadSprites(void)
{
    //tile to put in a res file
    //sprites->loadVarFile("grass");
    //sprites->loadVarFile("rock");

    std::list< std::string > textures = assets->getTextures();

    auto lit(textures.begin()), lend(textures.end());
    for(;lit!=lend;++lit)
    {
        std::cout << "Load asset texture : " << (*lit) << std::endl;
        sprites->loadVarFile((*lit));
    }

}
