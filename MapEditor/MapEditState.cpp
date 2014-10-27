#include "MapEditState.h"
#include "FileSystem.h"
#include <GamePath.h>
#include <iostream>

using namespace StiGame;
using namespace FS;

const char* MapEditState::NONE_TEXTURE = "tile/none";

MapEditState::MapEditState(MEMap *m_map)
{
    map = m_map;
    mapItem = nullptr;
    selectionStarted = false;
}

void MapEditState::handleEvent(StiGame::MouseMotionEventThrower *src, StiGame::MouseMotionEventArgs *args)
{
    if(selectionStarted)
    {
        int t_w = (args->getX() - selectionStart.getX()) / map->getTileDimension()->getWidth();
        t_w++;

        int t_h = (args->getY() - selectionStart.getY()) / map->getTileDimension()->getHeight();
        t_h++;
        mapItem->setSelectRectangleSize(t_w, t_h);
    }
}

void MapEditState::handleEvent(StiGame::MouseButtonEventThrower *src, StiGame::MouseButtonEventArgs *args)
{
    if(args->getSDLEvent()->button.state == SDL_PRESSED && !selectionStarted)
    {
        selectionStarted = true;
        selectionStart.setPoint(args->getX(), args->getY());
        mapItem->setSelectRectangle((selectionStart.getX()/ map->getTileDimension()->getWidth()) + mapItem->getPosition()->getX(),
                                    (selectionStart.getY() / map->getTileDimension()->getHeight()) + mapItem->getPosition()->getY(),
                                    1,
                                    1);
    }
    else
    {
        if(selectionStart.getX() >= 0 && selectionStart.getY() >= 0 && selectionStarted)
        {

            int t_w = (args->getX() - selectionStart.getX()) / map->getTileDimension()->getWidth();
            t_w++;

            int t_h = (args->getY() - selectionStart.getY()) / map->getTileDimension()->getHeight();
            t_h++;

            mapItem->setSelectRectangle((selectionStart.getX()/ map->getTileDimension()->getWidth()) + mapItem->getPosition()->getX(),
                                        (selectionStart.getY() / map->getTileDimension()->getHeight()) + mapItem->getPosition()->getY(),
                                            t_w,
                                            t_h);

            selectionStarted = false;

        }
    }
}

MapEditState::~MapEditState()
{

}

void MapEditState::onStart(void)
{
    running = true;
    sprites = new SpriteLibrary(viewport->getRenderer());

    scanTextures();

    //loading textures into sprites library

    auto tit(availableTextures.begin()), tend(availableTextures.end());
    for(;tit!=tend;++tit)
    {
        sprites->loadVarFile((*tit));
    }
    std::string defTex (NONE_TEXTURE);
    mapItem = new MapItem(map, sprites, defTex);
    mapItem->setDimension(width, height);

    mapItem->setSelectRectangle(0, 0, 0, 0);

    KeyEventThrower::subscribe(this);
    MouseButtonEventThrower::subscribe(this);
    MouseMotionEventThrower::subscribe(this);

    add(mapItem);
    add(&editItem);

    viewport->clearPreviousStates();
}

void MapEditState::onResize(int m_width, int m_height)
{
    editItem.setWidth(m_width);
    if(mapItem != nullptr)
    {
        mapItem->setDimension(m_width, m_height - editItem.getHeight());
    }

    editItem.setPoint(0, m_height - editItem.getHeight());
}

void MapEditState::handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args)
{
    SDL_KeyboardEvent *evt = args->getKeyboardEvent();

    if(evt->keysym.sym == SDLK_UP)
    {
        mapItem->moveView(0, -1);
    }
    else if(evt->keysym.sym == SDLK_DOWN)
    {
        mapItem->moveView(0, 1);
    }
    else if(evt->keysym.sym == SDLK_LEFT)
    {
        mapItem->moveView(-1, 0);
    }
    else if(evt->keysym.sym == SDLK_RIGHT)
    {
        mapItem->moveView(1, 0);
    }

    editItem.update(mapItem);
}

void MapEditState::scanTextures(void)
{
    std::string path = GamePath::getFilepath(AssetSprite, "tile/");
    std::vector<Entry*> files = FileSystem::ListDirectory(path);

    auto fit(files.begin()), fend(files.end());

    for(;fit!=fend;++fit)
    {
        if((*fit)->endsWith(".spr"))
        {

            std::string t_name = "tile/" + (*fit)->getNameWithoutExtension();
            availableTextures.push_back(t_name);
        }
    }

}
