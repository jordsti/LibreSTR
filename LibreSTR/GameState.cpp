#include "GameState.h"
#include <Viewport.h>
#include <iostream>

using namespace StiGame;

GameState::GameState(GameMap *m_gameMap) :
    BaseGameState()
{
    //ctor
    gameMap = m_gameMap;
    background.setRGB(0, 0, 0);

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
    running = true;
}

void GameState::drawBaseMap(void)
{
    baseMap = new Surface(gameMap->getWidth() * Tile::TILE_WIDTH, gameMap->getHeight() * Tile::TILE_WIDTH);
    baseMap->fill(&background);

    SDL_Rect dst;
    dst.w = Tile::TILE_WIDTH;
    dst.h = Tile::TILE_HEIGHT;

    Sprite *sprGrass = sprites->getSprite("grass");
    Sprite *sprBlock = sprites->getSprite("rock");

    Surface *sur;

    for(int y=0; y<gameMap->getHeight(); y++)
    {
        dst.y = y * Tile::TILE_HEIGHT;
        for(int x=0; x<gameMap->getWidth(); x++)
        {
            dst.x = x * Tile::TILE_WIDTH;

            Tile *t = gameMap->get(x, y);
            //draw grass on all tile
            sur = sprGrass->getCurrentSurface();

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

    //saving image for debug purpose
    baseMap->saveBmp("map.bmp");
}

void GameState::loadSprites(void)
{
    sprites->loadVarFile("grass");
    sprites->loadVarFile("rock");
    sprites->loadVarFile("titanium");
    sprites->loadVarFile("gaz");
}
