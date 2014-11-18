#include "GameState.h"
#include <Viewport.h>
#include <iostream>
#include "GameOverlay.h"
#include <OverlayGameAction.h>
#include "ViewMoveAction.h"
#include "ToggleMiniMapAction.h"
#include "ToggleShowFPSAction.h"
#include "ToggleConsole.h"
#include "GamePath.h"

using namespace StiGame;
using namespace Gui;

const int GameState::VIEW_MOVE_DX = 32;
const int GameState::VIEW_MOVE_DY = 32;
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

    currentPlayer = game->getPlayer(1);

    textColor.setRGB(250, 250, 250);

    lblFps.setForeground(&textColor);
    lblFps.setCaption("FPS : 0");
    lblFps.setVisible(false);
    lblFps.doAutosize();

    background.setRGB(0, 0, 0);
    viewX = 0;
    viewY = 0;

    //base building menu
    baseMenu.setCaption("Base Action");
    baseMenu.setCloseIcon(GamePath::getFilepath(AssetRoot, "close_radial.png"));
    baseMenu.setDimension(200, 300);
    baseMenu.setPoint(30, 30);

    baseCreateWorker = new RadialItem(0, "Create Worker", GamePath::getFilepath(AssetRoot, "worker16.png"), GamePath::getFilepath(AssetRoot, "worker16_hover.png"));
    baseMenu.addItem(baseCreateWorker);
    baseMenu.setVisible(false);

    console.setVisible(false);
    console.pushLine("LibreSTR Game State initializing...");

    std::string map_info = "Map size : " + std::to_string(pmap->getWidth()) + "x" + std::to_string(pmap->getHeight());
    console.pushLine(map_info);

    _items.push_back(&lblFps);
    _items.push_back(&baseMenu);
    _items.push_back(&console);
    _items.push_back(&unitInfo);

    baseMenu.subscribe(this);

    unitInfo.setVisible(false);

    selectColor.setRGBA(10, 10, 120, 120);
    multiselect = false;
}


GameState::~GameState()
{
    //dtor
}

void GameState::handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *args)
{
    if(src == &baseMenu)
    {
        //radial base menu
        if(selectedUnits.size() == 1)
        {
            Unit *unit = selectedUnits[0];
            if(unit->getType() == UT_Building)
            {
                Building *b = dynamic_cast<Building*>(unit);

                if(game->createWorker(currentPlayer, b))
                {
                    //closing radial menu
                    baseMenu.setVisible(false);
                }
                else
                {
                    std::string errorMsg = game->getGameError();
                    std::cout << errorMsg << std::endl;
                }
            }
        }
    }
}

void GameState::unload(void)
{
    clearActions();
    Player::ResetPlayerId();
    viewport->clearPreviousStates();
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


    //unit info panel
    unitInfo.setPoint(width - unitInfo.getWidth(), height - unitInfo.getHeight());

    //lbl fps position
    lblFps.setPoint(m_width - lblFps.getWidth() - 100, m_height - lblFps.getHeight() - 5);

    console.setDimension(m_width/2, m_height/2);
    console.setPoint(32, 32);
    std::string cline = "Setting view dimension to : " + std::to_string(m_width) + "x" + std::to_string(m_height);
    console.pushLine(cline);
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

    ToggleConsole *toggleConsole = new ToggleConsole(&console);
    actions.push_back(toggleConsole);

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

void GameState::handleEvent(MouseMotionEventThrower *src, MouseMotionEventArgs *args)
{
    mousePosition.setPoint(args->getX(), args->getY());

    MPoint pt (args->getX(), args->getY());

    auto vit(_items.begin()), vend(_items.end());
    for(;vit!=vend;++vit)
    {
        if((*vit)->isVisible() && (*vit)->contains(&pt))
        {
            Point dpt = (*vit)->diffPoint(&pt);
            (*vit)->onMouseMotion(&dpt);
        }
    }

    if(multiselect)
    {
        selectRect.setDimension(args->getX() - selectStartPt.getX(), args->getY() - selectStartPt.getY());
    }
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

    std::string moveView = "Moving view point to : " + std::to_string(viewX) + "; " + std::to_string(viewY);
    console.pushLine(moveView);

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

    game->tick();

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

    if(lblFps.isVisible())
    {
        lblFps.setCaption("FPS : "+std::to_string(viewport->getFps()));
    }

    //base building menu
    if(selectedUnits.size() == 1 && baseMenu.isVisible())
    {
        Unit *unitSelected = selectedUnits[0];
        if(unitSelected->getType() == UT_Building)
        {
            Point pt (unitSelected->getX() - viewX, (unitSelected->getY() + topHud->getHeight()) - viewY);
            baseMenu.setPoint(&pt);
        }
    }

    auto vit(_items.begin()), vend(_items.end());
    for(;vit!=vend;++vit)
    {
        Item *i = (*vit);
        if(i->isVisible())
        {
            Surface *isur = i->render();
            Texture itex (renderer, isur);
            itex.setBlendMode(SDL_BLENDMODE_BLEND);
            itex.setAlphaMod(150);
            itex.renderCopy(i);
        }
    }

    //draw select rectangle

    if(multiselect && selectRect.getWidth() > 0 && selectRect.getHeight() > 0)
    {
        Rectangle relRect;
        relRect.setPoint(selectRect.getX() - viewX, (selectRect.getY() - viewY) + topHud->getHeight());
        relRect.setDimension(selectRect.getWidth(), selectRect.getHeight());

        Surface *isur = new Surface(relRect.getWidth(), relRect.getHeight());
        isur->fill(&selectColor);

        Texture itex (renderer, isur);
        itex.setBlendMode(SDL_BLENDMODE_BLEND);
        itex.setAlphaMod(120);
        itex.renderCopy(&relRect);
    }

}

void GameState::handleEvent(MouseButtonEventThrower *src, MouseButtonEventArgs *args)
{
    Point mpt (args->getX(), args->getY());
    bool unitSelected = false;
    if(args->getMouseButton() == MB_LEFT && !args->isDown())
    {
        Dimension d = miniMap->getDimension();
        Rectangle miniMapZone(0, height - d.getHeight(), d.getWidth(), d.getHeight());
        if(miniMapZone.contains(args->getX(), args->getY()))
        {
            Point pt (args->getX(),args->getY() - (height - d.getHeight()));
            miniMap->mouseClick(pt);
            return;
        }

        auto vit(_items.begin()), vend(_items.end());
        for(;vit!=vend;++vit)
        {
            if((*vit)->isVisible() && (*vit)->contains(&mpt))
            {
                //todo add diff point method into stigame
                Point rpt = (*vit)->diffPoint(&mpt);
                (*vit)->onClick(&rpt);
            }
        }

    }

    if(args->getMouseButton() == MB_LEFT && !args->isDown() && multiselect)
    {
        multiselect = false;
    }
    else if(args->getMouseButton() == MB_LEFT && args->isDown() && !multiselect)
    {
        //single selection case
        Point gamePoint (mpt.getX() + viewX, (mpt.getY() - topHud->getHeight()) + viewY);

        int ucount = pmap->getBuildingsCount();
        for(int i=0; i<ucount; i++)
        {
            Building *b = pmap->getBuilding(i);
            Rectangle bRect (b->getX(), b->getY(), b->getWidth(), b->getHeight());

            if(bRect.contains(&gamePoint))
            {
                //std::cout << b->getName() << std::endl;

                selectedUnits.clear();
                selectedUnits.push_back(b);

                unitInfo.setUnit(b);
                unitInfo.setVisible(true);

                baseMenu.setVisible(true);
                return;
            }

        }

        //no return, clearing selection
        unitInfo.setUnit(nullptr);
        unitInfo.setVisible(false);
        //baseMenu.setVisible(false);

        //multiselect
        multiselect = true;
        selectRect.setPoint(viewX + args->getX(), viewY + (args->getY() - topHud->getHeight()));
        selectRect.setDimension(0, 0);
        selectStartPt.setPoint(args->getX(), args->getY());

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
