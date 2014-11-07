#include "GameState.h"
#include <Viewport.h>
#include <iostream>
#include "GameOverlay.h"
#include <OverlayGameAction.h>
#include "ViewMoveAction.h"
#include "ToggleMiniMapAction.h"
#include "ToggleShowFPSAction.h"
#include "GamePath.h"

using namespace StiGame;

const int GameState::VIEW_MOVE_DX = 16;
const int GameState::VIEW_MOVE_DY = 16;
const int GameState::VIEW_RECT_ZONE = 48;

GameState::GameState(AssetManager *m_assets) :
    BaseGameState()
{
    //ctor
    assets = m_assets;

    game = new GameObject(m_assets, 300, 200);
    game->initGame();
    pmap = game->getPlayerMap(1);
    miniMap = new MiniMap(this, pmap, 300, 200, 22);
    topHud = new TopHud(m_assets, game->getPlayer(1));

    textColor.setRGB(250, 250, 250);

    lblFps.setForeground(&textColor);
    lblFps.setCaption("FPS : 0");
    lblFps.setVisible(false);
    lblFps.doAutosize();
    //gameMap = new GameMap();
    //gameMap->load("test.map", assets)

    background.setRGB(0, 0, 0);
    viewX = 0;
    viewY = 0;

    //todo
    //baseMenu.setVisible(false);
    baseMenu.setCaption("Base Action");
    baseMenu.setCloseIcon(GamePath::getFilepath(AssetRoot, "close_radial.png"));
    baseMenu.setDimension(300, 300);
    RadialItem *ri = new RadialItem("Create Worker", GamePath::getFilepath(AssetRoot, "worker16.png"), GamePath::getFilepath(AssetRoot, "worker16.png"));
    baseMenu.addItem(ri);
    /*baseMenu.addItem(ri);
    baseMenu.addItem(ri);
    baseMenu.addItem(ri);
    baseMenu.addItem(ri);
    baseMenu.addItem(ri);*/


}


GameState::~GameState()
{
    //dtor
}


void GameState::unload(void)
{
    clearActions();
    Player::ResetPlayerId();
    delete game;
    //delete miniMap;
    delete sprites;
    delete baseMap;
    delete topHud;
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


    //view movement rect update
    viewRectUp.setWidth(m_width);
    viewRectUp.setHeight(VIEW_RECT_ZONE + topHud->getHeight());

    viewRectDown.setWidth(m_width);
    viewRectDown.setHeight(VIEW_RECT_ZONE);
    viewRectDown.setY(height - VIEW_RECT_ZONE);

    viewRectLeft.setHeight(m_height);
    viewRectLeft.setWidth(VIEW_RECT_ZONE);

    viewRectRight.setHeight(m_height);
    viewRectRight.setWidth(VIEW_RECT_ZONE);
    viewRectRight.setX(width - VIEW_RECT_ZONE);

    //lbl fps position
    lblFps.setPoint(m_width - lblFps.getWidth() - 100, m_height - lblFps.getHeight() - 5);
}

void GameState::onStart(void)
{
    sprites = new SpriteLibrary(viewport->getRenderer());
    loadSprites();

    GameOverlay *overlay = new GameOverlay();
    overlay->setState(this);
    //KeyEventThrower::subscribe(overlay);
    setGameMenu(overlay);

    //BaseGameAction *oaction = OverlayGameAction::GetDefaultOverlayGameAction(this);

    //actions.push_back(oaction);

    //view movement action
    ViewMoveAction *vaction;

    vaction = new ViewMoveAction(this, "view_move_up", 0, -VIEW_MOVE_DX);
    actions.push_back(vaction);

    vaction = new ViewMoveAction(this, "view_move_down", 0, VIEW_MOVE_DX);
    actions.push_back(vaction);

    vaction = new ViewMoveAction(this, "view_move_left", -VIEW_MOVE_DY, 0);
    actions.push_back(vaction);

    vaction = new ViewMoveAction(this, "view_move_right", VIEW_MOVE_DY, 0);
    actions.push_back(vaction);

    ToggleMiniMapAction *taction = new ToggleMiniMapAction(miniMap);
    actions.push_back(taction);

    ToggleShowFPSAction *fpsAction = new ToggleShowFPSAction(&lblFps);
    actions.push_back(fpsAction);

    auto vit(actions.begin()), vend(actions.end());
    for(;vit!=vend;++vit)
    {
        ActionMap *amap = assets->getBindings()->getBinding((*vit)->getName());
        if(amap != 0)
        {
            (*vit)->setActionMap(amap);
        }
    }

    KeyEventThrower::subscribe(this);
    MouseButtonEventThrower::subscribe(this);
    MouseMotionEventThrower::subscribe(this);

    /*Building *b1 = new Building();
    gameMap->forcePlaceBuilding(new Building(), 64, 64);
    gameMap->forcePlaceBuilding(b1, 6, 6);*/

    drawBaseMap();
    running = true;

    //set view position
    Building *playerBase = pmap->getBuilding(0);

    int n_x = playerBase->getX();
    int n_y = playerBase->getY();

    n_x -= width / 2;
    n_y -= height / 2;

    n_x /= Tile::TILE_WIDTH;
    n_y /= Tile::TILE_HEIGHT;

    if(n_x < 0)
        n_x = 0;
    else if(n_x > pmap->getWidth() - (width/Tile::TILE_WIDTH))
        n_x = pmap->getWidth() - (width/Tile::TILE_WIDTH);

    if(n_y < 0)
        n_y = 0;
    else if(n_y > pmap->getHeight() - (height/Tile::TILE_HEIGHT))
        n_y = pmap->getHeight() - (height/Tile::TILE_HEIGHT);

    setViewPoint(n_x, n_y);
    miniMap->setViewPoint(viewX, viewY);

}

MiniMap* GameState::getMiniMap(void)
{
    return miniMap;
}

void GameState::tickMouseViewMovement(void)
{
    int dx = 0;
    int dy = 0;

    Rectangle miniMapRect(0,
                          height - miniMap->getHeight(),
                          miniMap->getWidth(),
                          miniMap->getHeight());

    if(viewRectUp.contains(&mousePosition))
        dy -= VIEW_MOVE_DY;


    if(viewRectDown.contains(&mousePosition) && !miniMapRect.contains(&mousePosition))
        dy += VIEW_MOVE_DY;


    if(viewRectLeft.contains(&mousePosition) && !miniMapRect.contains(&mousePosition))
        dx -= VIEW_MOVE_DX;


    if(viewRectRight.contains(&mousePosition))
        dx += VIEW_MOVE_DX;


    if(dx != 0 || dy != 0)
        moveViewPoint(dx, dy);

}

void GameState::handleEvent(KeyEventThrower *src, KeyEventArgs *args)
{
    if(args->getKeyboardEvent()->keysym.sym == SDLK_ESCAPE && args->getState() == KS_UP)
    {
        if(!gameMenu->isVisible())
        {
            openGameMenu();
        }
        else
        {
            closeGameMenu();
        }
    }
}

void GameState::handleEvent(StiGame::MouseMotionEventThrower *src, StiGame::MouseMotionEventArgs *args)
{
    mousePosition.setPoint(args->getX(), args->getY());
}

void GameState::moveViewPoint(int dx, int dy)
{
    int tmpX = viewX + dx;
    int tmpY = viewY + dy;

    if((tmpX >= 0 && tmpX <= ((pmap->getWidth() + 1) * Tile::TILE_WIDTH) - width) && dx != 0)
    {
        viewX = tmpX;
    }

    if((tmpY >= 0 && tmpY <= ((pmap->getHeight() + 1) * Tile::TILE_HEIGHT) - (height - topHud->getHeight())) && dy != 0)
    {
        viewY = tmpY;
    }

    miniMap->setViewPoint(viewX, viewY);
}

void GameState::setViewPoint(int t_x, int t_y)
{
    viewX = t_x * Tile::TILE_WIDTH;
    viewY = t_y * Tile::TILE_HEIGHT;
}

void GameState::onPaint(SDL_Renderer *renderer)
{
    //todo move this plz !
    tickActions();
    tickMouseViewMovement();

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


    int mb = pmap->getBuildingsCount();
    Rectangle vwRect (viewX, viewY, width, height - topHud->getHeight());

    for(int i=0; i<mb; i++)
    {
        Building *b = pmap->getBuilding(i);
        Point p2 (b->getX() + b->getWidth(), b->getY() + b->getHeight());

        if(vwRect.contains(&p2) || vwRect.contains(b))
        {
            Sprite *sprBuilding = sprites->getSprite(b->getSpriteName());
            sprBuilding->setPoint(b->getX() - viewX, (b->getY()+topHud->getHeight()) - viewY);
            sprBuilding->render();
        }
    }

    renderGui(renderer);

    BaseGameState::onPaint(renderer);
}

void GameState::renderGui(SDL_Renderer *renderer)
{
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

    //fps label
    if(lblFps.isVisible())
    {
        lblFps.setCaption("FPS : "+std::to_string(viewport->getFps()));
        Surface *surLbl = lblFps.render();
        Texture texLbl (renderer, surLbl);
        texLbl.renderCopy(&lblFps);
    }

    if(baseMenu.isVisible())
    {
        //test radial menu section
        Surface *rmenu = baseMenu.render();
        Texture texR (renderer, rmenu);
        texR.setBlendMode(SDL_BLENDMODE_ADD);
        Point rdst (0,0);
        texR.renderCopy(&rdst);
    }


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
    baseMap = new Surface(pmap->getWidth() * Tile::TILE_WIDTH, pmap->getHeight() * Tile::TILE_WIDTH);
    baseMap->fill(&background);

    SDL_Rect dst;
    dst.w = Tile::TILE_WIDTH;
    dst.h = Tile::TILE_HEIGHT;

    Sprite *sprDefault = sprites->getSprite(pmap->getDefaultTexture());

    Surface *sur;

    for(int y=0; y<pmap->getHeight(); y++)
    {
        dst.y = y * Tile::TILE_HEIGHT;
        for(int x=0; x<pmap->getWidth(); x++)
        {
            dst.x = x * Tile::TILE_WIDTH;

            Tile *t = pmap->get(x, y);
            //draw grass on all tile
            sur = sprDefault->getCurrentSurface();
            baseMap->blit(sur, &dst);

            if(t->getTextureId() != pmap->getDefaultTextureId())
            {
                Sprite *sprTile = sprites->getSprite(pmap->getTexture(t->getTextureId()));
                sur = sprTile->getCurrentSurface();
                baseMap->blit(sur, &dst);
            }

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
