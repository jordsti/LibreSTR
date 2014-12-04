#include "GameState.h"
#include <Viewport.h>
#include <iostream>
#include "GameOverlay.h"
#include <OverlayGameAction.h>
#include "ViewMoveAction.h"
#include "ToggleMiniMapAction.h"
#include "ToggleShowFPSAction.h"
#include "ToggleConsole.h"
#include "PauseGameAction.h"
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
    placingBuilding = false;
    game = new GameObject(m_assets, 300, 200, &console);
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
    baseMenu.setCaption(assets->getBaseIdentity()->getName());
    baseMenu.setCloseIcon(GamePath::getFilepath(AssetRoot, "close_radial.png"));
    baseMenu.setDimension(220, 300);
    baseMenu.setPoint(30, 30);

    baseCreateWorker = new RadialItem(0,
                                      "Create Worker",
                                      GamePath::getFilepath(AssetRoot, assets->getWorkerIdentity()->getRadialIcon()),
                                      GamePath::getFilepath(AssetRoot, assets->getWorkerIdentity()->getRadialHoverIcon()));

    baseMenu.addItem(baseCreateWorker);
    baseMenu.setVisible(false);



    barrackMenu.setCaption(assets->getBarrackIdentity()->getName());
    //put radial close icon into assets.def
    barrackMenu.setCloseIcon(GamePath::getFilepath(AssetRoot, "close_radial.png"));
    barrackMenu.setDimension(220, 300);

    barrackCreateMelee = new RadialItem(0,
                                        "Create Melee",
                                        GamePath::getFilepath(AssetRoot, assets->getMeleeIdentity()->getRadialIcon()),
                                        GamePath::getFilepath(AssetRoot, assets->getMeleeIdentity()->getRadialHoverIcon()));

    barrackMenu.addItem(barrackCreateMelee);
    barrackMenu.setVisible(false);

    console.setVisible(false);
    console.pushLine("LibreSTR Game State initializing...");

    std::string map_info = "Map size : " + std::to_string(pmap->getWidth()) + "x" + std::to_string(pmap->getHeight());
    console.pushLine(map_info);

    _items.push_back(&lblFps);
    _items.push_back(&baseMenu);
    _items.push_back(&barrackMenu);
    _items.push_back(&console);
    _items.push_back(&unitInfo);
    _items.push_back(&lblError);

    baseMenu.subscribe(this);
    barrackMenu.subscribe(this);

    unitInfo.setVisible(false);
    unitInfo.loadAssets(assets);
    unitInfo.setGameState(this);

    selectColor.setRGBA(10, 10, 120, 120);
    multiselect = false;

    lblError.setPoint(5, topHud->getHeight() + 2);
    lblError.setVisible(false);

    lblPaused.setFont(lblPaused.getStyle()->getBigFont());
    lblPaused.setCaption("Pause");
    lblPaused.setVisible(false);

    _items.push_back(&lblPaused);

    paused = false;
}

GameState::~GameState()
{
    //dtor
}

void GameState::setPause(bool m_paused)
{
    paused = m_paused;
    lblPaused.setVisible(paused);
    if(!paused)
    {
        game->resetLastTick();
    }
}

bool GameState::getPause(void)
{
    return paused;
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

                if(game->createWorker(currentPlayer, b) && b->getBuildingType() == BT_Base)
                {
                    //closing radial menu
                    baseMenu.setVisible(false);
                }
                else
                {
                    std::string errorMsg = game->getGameError();
                    //std::cout << errorMsg << std::endl;
                    lblError.setCaption(errorMsg);
                    lblError.setVisible(true);
                }
            }
        }
    }
    else if(src == &barrackMenu)
    {
        if(selectedUnits.size() == 1)
        {
            Unit *unit = selectedUnits[0];
            if(unit->getType() == UT_Building)
            {
                Building *b = dynamic_cast<Building*>(unit);

                //todo
                if(b->getBuildingType() == BT_Barrack)
                {
                    if(args->getSelection() == barrackCreateMelee)
                    {
                        if(game->createMelee(currentPlayer, b))
                        {
                            barrackMenu.setVisible(false);
                        }
                        else
                        {
                            std::string errorMsg = game->getGameError();
                            //std::cout << errorMsg << std::endl;
                            lblError.setCaption(errorMsg);
                            lblError.setVisible(true);
                        }
                    }

                }
            }
        }
    }
}

void GameState::unload(void)
{
    clearActions();
    Player::ResetPlayerId();

    delete game;
    //delete miniMap;
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

    lblPaused.setPoint((m_width - lblPaused.getWidth())/2, (m_height - lblPaused.getHeight())/2);
}

void GameState::placeBuilding(GroundUnit *m_builder, BuildingIdentity *toPlaceId)
{
    placingBuilding = true;
    builder = m_builder;
    buildingId = toPlaceId;
    //using current mouse point
    updatePlaceBuilding();
}

void GameState::onStart(void)
{
    sprites.setRenderer(viewport->getRenderer());
    groundUnitSprites.setRenderer(viewport->getRenderer());

    loadSprites();

    groundUnitSpritesManager.setLibrary(&groundUnitSprites);

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

    PauseGameAction *pauseGame = new PauseGameAction(this);
    actions.push_back(pauseGame);


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

void GameState::updatePlaceBuilding(void)
{
    int t_x = (viewX + mousePosition.getX())/Tile::TILE_WIDTH;
    int t_y = (viewY + (mousePosition.getY()-topHud->getHeight()))/Tile::TILE_HEIGHT;

    buildingPos.setPoint(t_x * Tile::TILE_WIDTH, t_y * Tile::TILE_HEIGHT);
}

void GameState::tickMouseViewMovement(void)
{
    int dx = 0;
    int dy = 0;

    Rectangle miniMapRect(0,
                          height - miniMap->getHeight(),
                          miniMap->getWidth(),
                          miniMap->getHeight());

    if(unitInfo.isVisible() && unitInfo.contains(&mousePosition))
    {
        return;
    }

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
    if(!paused)
    {
        groundUnitSpritesManager.tick();

        if(placingBuilding)
        {
            updatePlaceBuilding();
        }

        game->tick();
    }

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

    renderUnits(renderer);

    if(placingBuilding)
    {
        Sprite *sprPlace = sprites.getSprite(buildingId->getPlacedSprite());
        sprPlace->setPoint(buildingPos.getX() - viewX, (buildingPos.getY()+topHud->getHeight()) - viewY);
        sprPlace->render();
    }

    renderGui(renderer);

    BaseGameState::onPaint(renderer);
}

void GameState::renderUnits(SDL_Renderer *renderer)
{
    int mb = pmap->getBuildingsCount();
    Rectangle vwRect (viewX, viewY, width, height - topHud->getHeight());

    for(int i=0; i<mb; i++)
    {
        Building *b = pmap->getBuilding(i);
        Point p2 (b->getX() + b->getWidth(), b->getY() + b->getHeight());

        if(vwRect.contains(&p2) || vwRect.contains(b))
        {
            Sprite *sprBuilding = sprites.getSprite(b->getSpriteName());
            sprBuilding->setPoint(b->getX() - viewX, (b->getY()+topHud->getHeight()) - viewY);
            sprBuilding->render();
        }
    }

    int mu = pmap->getGroundUnitsCount();
    for(int i=0; i<mu; i++)
    {
        GroundUnit *u = pmap->getGroundUnit(i);
        Point middlePt = u->middle();
        Point endPt = u->maxPoint();

        if(vwRect.contains(u) ||
           vwRect.contains(&middlePt) ||
           vwRect.contains(&endPt))
        {
            ClonedDirectionSprite *guSprite = groundUnitSpritesManager.getUnitSprite(u);
            guSprite->setPoint(u->getX() - viewX, (u->getY()+topHud->getHeight()) - viewY);
            guSprite->render();

        }
    }
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

    //barrack building menu
    if(selectedUnits.size() == 1 && barrackMenu.isVisible())
    {
        Unit *unitSelected = selectedUnits[0];
        if(unitSelected->getType() == UT_Building)
        {
            Point pt (unitSelected->getX() - viewX, (unitSelected->getY() + topHud->getHeight()) - viewY);
            barrackMenu.setPoint(&pt);
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
    //building placing
    if(args->getMouseButton() == MB_LEFT && placingBuilding && args->isDown())
    {
        std::cout << buildingPos.getX() << "; " << buildingPos.getY() << std::endl;

        if(pmap->isBuildingLocationValid(buildingId, &buildingPos))
        {
            if(currentPlayer->getMetalCount() >= buildingId->getMetalCost() && currentPlayer->getGazCount() >= buildingId->getGazCost())
            {
                if(selectedUnits.size() > 0)
                {
                    Unit *unit = selectedUnits[0];
                    game->buildBuilding(buildingId, unit, currentPlayer, buildingPos.getX() / Tile::TILE_WIDTH, buildingPos.getY() / Tile::TILE_HEIGHT);
                    placingBuilding = false;
                    return;
                }
            }
            else
            {
                std::string msg = "Not Enough Resource";
                lblError.setCaption(msg);
                lblError.setVisible(true);
                console.pushLine("Game Error : " + msg);
                placingBuilding = false;
                return;
            }
        }
        else
        {
            std::string msg = "Invalid Building Location";
            lblError.setCaption(msg);
            lblError.setVisible(true);
            console.pushLine("User Choice Error : " + msg);
        }


    }

    if(args->getMouseButton() == MB_RIGHT && placingBuilding)
    {
        placingBuilding = false;
        return;
    }


    Point mpt (args->getX(), args->getY());
    bool unitSelected = false;
    if(args->getMouseButton() == MB_LEFT && args->isDown())
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
                return;
            }
        }

    }

    if(args->getMouseButton() == MB_RIGHT && !args->isDown())
    {
        StiGame::Point targetPt (viewX + args->getX(), viewY + (args->getY() - topHud->getHeight()));

        if(selectedUnits.size() > 0)
        {
            //units deplacement
            bool handled = false;
            StiGame::Point tilePt (targetPt.getX() / Tile::TILE_WIDTH, targetPt.getY() / Tile::TILE_HEIGHT);

            if(tilePt.getX() >= 0 &&
                    tilePt.getY() >= 0 &&
                    tilePt.getX() < pmap->getWidth() &&
                    tilePt.getY() < pmap->getHeight())
            {

                Tile *tile = pmap->get(tilePt.getX(), tilePt.getY());

                if(tile->containsResource())
                {
                    //resource harvesting
                    auto vit(selectedUnits.begin()), vend(selectedUnits.end());
                    for(;vit!=vend;++vit)
                    {
                        Unit *unit = (*vit);
                        if(unit->getType() == UT_Ground && unit->getOwner() == currentPlayer)
                        {
                            game->harvestResource(unit, &targetPt);
                        }
                    }


                    handled = true;
                }

            }

            //building reparation
            if(!handled)
            {
                Unit *u = selectedUnits[0];
                if(u->getType() == UT_Ground && u->getOwner() == currentPlayer)
                {
                    GroundUnit *gu = dynamic_cast<GroundUnit*>(u);
                    if(gu->getIdentity()->isCanBuild())
                    {
                        int bc = pmap->getBuildingsCount();
                        for(int i=0; i<bc; i++)
                        {
                            Building *b = pmap->getBuilding(i);
                            if(b->getOwner() == gu->getOwner())
                            {
                                if(b->contains(&targetPt) && b->getCurrentHealth() <  b->getMaxHealth())
                                {
                                    game->repairBuilding(b, gu, currentPlayer);
                                    handled = true;
                                }
                            }
                        }
                    }
                }
            }


            //units deplacement
            if(!handled)
            {

                auto vit(selectedUnits.begin()), vend(selectedUnits.end());
                Unit *firstUnit = nullptr;
                for(;vit!=vend;++vit)
                {
                    if(firstUnit == nullptr)
                    {
                        firstUnit = (*vit);
                    }

                    Unit *unit = (*vit);
                    if(unit->getType() == UT_Ground && unit->getOwner() == currentPlayer)
                    {
                        if(firstUnit != unit)
                        {
                            StiGame::Point dpt = firstUnit->diffPoint(unit);
                            StiGame::Point dtpt (targetPt.getX() + dpt.getX(), targetPt.getY() + dpt.getY());
                            game->moveGroundUnit(unit, &dtpt);
                        }
                        else
                        {
                            game->moveGroundUnit(unit, &targetPt);
                        }
                    }
                }

            }

        }
    }

    if(args->getMouseButton() == MB_LEFT && !args->isDown() && multiselect)
    {
        multiselect = false;
        //todo completing multiselect
        selectedUnits.clear();
        int uc = pmap->getGroundUnitsCount();
        for(int i=0; i<uc; i++)
        {
            GroundUnit *unit = pmap->getGroundUnit(i);

            Point mpt = unit->middle();

            if(selectRect.contains(&mpt) && unit->getOwner() == currentPlayer)
            {
                selectedUnits.push_back(unit);
            }
        }

        if(selectedUnits.size() == 1)
        {
            unitInfo.setUnit(selectedUnits[0]);
            unitInfo.setVisible(true);
        }
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

            if(bRect.contains(&gamePoint) && b->getOwner() == currentPlayer)
            {
                //std::cout << b->getName() << std::endl;

                selectedUnits.clear();
                selectedUnits.push_back(b);

                unitInfo.setUnit(b);
                unitInfo.setVisible(true);

                if(b->getState() == BS_Builded && b->getBuildingType() == BT_Base)
                {
                    //command center menu
                    baseMenu.setVisible(true);
                }
                else
                {
                    baseMenu.setVisible(false);
                }

                if(b->getState() == BS_Builded && b->getBuildingType() == BT_Barrack)
                {
                    barrackMenu.setVisible(true);
                }
                else
                {
                    barrackMenu.setVisible(false);
                }

                return;
            }

        }

        //units check
        ucount = pmap->getGroundUnitsCount();
        for(int i=0; i<ucount; i++)
        {
            GroundUnit *u = pmap->getGroundUnit(i);
            Rectangle uRect (u->getX(), u->getY(), u->getWidth(), u->getHeight());

            if(uRect.contains(&gamePoint) && u->getOwner() == currentPlayer)
            {
                selectedUnits.clear();
                selectedUnits.push_back(u);

                unitInfo.setUnit(u);
                unitInfo.setVisible(true);
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

    Sprite *sprDefault = sprites.getSprite(pmap->getDefaultTexture());

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
                Sprite *sprTile = sprites.getSprite(pmap->getTexture(t->getTextureId()));
                sur = sprTile->getCurrentSurface();
                baseMap->blit(sur, &dst);
            }

            if(t->containsResource())
            {
                Resource *rs = t->getResource();
                Sprite *sprRes = sprites.getSprite(rs->getTexture());

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
        sprites.loadVarFile((*lit));
    }

    std::list < std::string > _dSprites = assets->getDirectionSprites();

    auto dit(_dSprites.begin()), dend(_dSprites.end());
    for(;dit!=dend;++dit)
    {
        groundUnitSprites.loadVarFile((*dit));
    }

}
