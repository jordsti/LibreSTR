#include "MapEditMainMenu.h"
#include <GamePath.h>
#include <FileSystem.h>
#include <iostream>
#include "NewMapState.h"

using namespace StiGame;

using namespace Gui;
using namespace FS;

MapEditMainMenu::MapEditMainMenu() : GuiState()
{
    selectedMap = nullptr;
    initComponents();
}

MapEditMainMenu::~MapEditMainMenu()
{
}

void MapEditMainMenu::onResize(int m_width, int m_height)
{
    //setting location of all item

    MPoint curPoint;
    curPoint.setX(5);

    curPoint.setY(10);
    lblTitle.setPoint(&curPoint);


    curPoint.setY(50);

    btnLoadMap.setPoint(&curPoint);
    curPoint.setY(btnLoadMap.getY() + BTN_HEIGHT + 5);

    btnNewMap.setPoint(&curPoint);

    curPoint.setY(m_height - BTN_HEIGHT - 5);

    btnQuit.setPoint(&curPoint);

    curPoint.setX(BTN_WIDTH + 25);
    curPoint.setY(btnLoadMap.getY());

    listMaps.setPoint(&curPoint);
}

void MapEditMainMenu::unload(void)
{
    auto vit(mapFiles.begin()), vend(mapFiles.end());
    for(;vit!=vend;++vit)
    {
        listMaps.remove((*vit));
        delete (*vit);
    }
}

void MapEditMainMenu::handleEvent(EventThrower *src, EventArgs *evt)
{
    if(src == &btnQuit)
    {
        running = false;
    }
    else if(src == &btnLoadMap)
    {
        if(selectedMap != nullptr)
        {
            //load that map
            //and change state
        }
    }
    else if(src == &btnNewMap)
    {
        NewMapState *state = new NewMapState();
        viewport->push(state);
    }
}

void MapEditMainMenu::handleEvent(SelectionEventThrower *src, SelectionEventArgs *args)
{
    if(src == &listMaps)
    {
        auto vit(mapFiles.begin()), vend(mapFiles.end());
        for(;vit!=vend;++vit)
        {
            if(args->getSelection()->getId() == (*vit)->getId())
            {
                selectedMap = (*vit);
            }
        }
    }
}

void MapEditMainMenu::initComponents(void)
{
    btnLoadMap.setDimension(BTN_WIDTH, BTN_HEIGHT);
    btnNewMap.setDimension(BTN_WIDTH, BTN_HEIGHT);
    btnQuit.setDimension(BTN_WIDTH, BTN_HEIGHT);


    btnLoadMap.setCaption("Load Map");
    btnNewMap.setCaption("New Map");
    btnQuit.setCaption("Quit");

    listMaps.setFixedSize(200, 400);

    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("LibreSTR Map Editor");

    //reading maps dir

    std::string mapPath = GamePath::getFilepath(AssetRoot, "maps");
    std::vector<Entry*> entries = FileSystem::ListDirectory(mapPath);
    auto vit(entries.begin()), vend(entries.end());
    int i=0;
    for(;vit!=vend;++vit)
    {
        if((*vit)->type() == ET_File)
        {
            if((*vit)->endsWith(".map"))
            {
                MapFileVO *vo = new MapFileVO(i, (*vit));
                i++;
                listMaps.add(vo);
                mapFiles.push_back(vo);
            }
            else
            {
                //deleting those useless entry
                delete (*vit);
            }
        }
    }

    btnLoadMap.subscribe(this);
    btnNewMap.subscribe(this);
    btnQuit.subscribe(this);
    listMaps.subscribe(this);

    add(&btnLoadMap);
    add(&btnNewMap);
    add(&btnQuit);
    add(&listMaps);
    add(&lblTitle);
}
