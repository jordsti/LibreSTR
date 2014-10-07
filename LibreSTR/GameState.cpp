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
    topHud = new TopHud(m_assets);
    assets = m_assets;
    gameMap = m_gameMap;
    pmap = gameMap->GeneratePlayerMap(1);
    miniMap = new MiniMap(this, pmap, 300, 200, 22);

    //gameMap = new GameMap();
    //gameMap->load("test.map", assets)

    background.setRGB(0, 0, 0);
    viewX = 0;
    viewY = 0;

}


GameState::~GameState()
{
    //dtor
}


void GameState::unload(void)
{
    std::cout << "Is this called ?!?" << std::endl;
    clearActions();
    delete gameMap;
    delete miniMap;
    delete sprites;
    delete baseMap;
    delete topHud;
    delete pmap;
}

AssetManager* GameState::getAssets(void)
{
    return assets;
}

void GameState::quit(void)
{
    running = false;
}

void GameState::onResize(int m_width, int m_height)
{
    topHud->setWidth(m_width);
    BaseGameState::onResize(m_width, m_height);
    miniMap->setViewDimension(m_width, m_height);
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
    MouseButtonEventThrower::subscribe(this);

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

        miniMap->setViewPoint(viewX, viewY);
    }
}

void GameState::setViewPoint(int t_x, int t_y)
{
    /*if(t_x < gameMap->getWidth() - (width / Tile::TILE_WIDTH) && t_x >= 0)
    {
        viewX = t_x * Tile::TILE_WIDTH;
    }

    if(t_y < gameMap->getHeight() - (height / Tile::TILE_HEIGHT) && t_y >= 0)
    {
        viewY = t_y * Tile::TILE_HEIGHT;
    }*/
    viewX = t_x * Tile::TILE_WIDTH;
    viewY = t_y * Tile::TILE_HEIGHT;
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
    mapRect.h = height - topHud->getHeight();

    viewRect.x = 0;
    viewRect.y = topHud->getHeight();
    viewRect.w = width;
    viewRect.h = height - topHud->getHeight();


    Surface *buffer = new Surface(width, height);

    buffer->blit(baseMap, &mapRect, &viewRect);

    Texture tex (renderer, buffer);
    tex.renderCopy(&viewRect, &viewRect);


    //Hud
    Surface *surHud = topHud->render();

    Texture texHud (renderer, surHud);
    texHud.renderCopy(topHud);

    Surface *surMiniMap = miniMap->getSurface();
    Texture texMiniMap (renderer, surMiniMap);
    Point dst (0, height - texMiniMap.getHeight());

    texMiniMap.setBlendMode(SDL_BLENDMODE_BLEND);
    texMiniMap.setAlphaMod(160);
    texMiniMap.renderCopy(&dst);

    BaseGameState::onPaint(renderer);
}

void GameState::handleEvent(MouseButtonEventThrower *src, MouseButtonEventArgs *args)
{
    if(args->getMouseButton() == MB_LEFT && !args->isDown())
    {
        Dimension d = miniMap->getDimension();
        Rectangle miniMapZone(0, height - d.getHeight(), d.getWidth(), d.getHeight());
        if(miniMapZone.contains(args->getX(), args->getY()))
        {
            Point pt (args->getX(),args->getY() - (height - d.getHeight()));
            miniMap->mouseClick(pt);
        }
    }
}

void GameState::drawBaseMap(void)
{
    baseMap = new Surface(gameMap->getWidth() * Tile::TILE_WIDTH, gameMap->getHeight() * Tile::TILE_WIDTH);
    baseMap->fill(&background);

    SDL_Rect dst;
    dst.w = Tile::TILE_WIDTH;
    dst.h = Tile::TILE_HEIGHT;

    Sprite *sprDefault = sprites->getSprite(gameMap->getDefaultTexture());

    Surface *sur;

    for(int y=0; y<gameMap->getHeight(); y++)
    {
        dst.y = y * Tile::TILE_HEIGHT;
        for(int x=0; x<gameMap->getWidth(); x++)
        {
            dst.x = x * Tile::TILE_WIDTH;

            Tile *t = gameMap->get(x, y);
            //draw grass on all tile
            sur = sprDefault->getCurrentSurface();
            baseMap->blit(sur, &dst);

            if(t->getTextureId() != gameMap->getDefaultTextureId())
            {
                Sprite *sprTile = sprites->getSprite(gameMap->getTexture(t->getTextureId()));
                sur = sprTile->getCurrentSurface();
                baseMap->blit(sur, &dst);
            }

            /*if(t->getType() == TT_Block)
            {
                sur = sprBlock->getCurrentSurface();

                baseMap->blit(sur, &dst);
                //draw a rock
            }*/

            if(t->containsResource())
            {
                Resource *rs = t->getResource();
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
        //std::cout << "Load asset texture : " << (*lit) << std::endl;
        sprites->loadVarFile((*lit));
    }

}
