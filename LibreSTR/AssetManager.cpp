#include "AssetManager.h"
#include <VarFile.h>
#include <GamePath.h>
#include <KeyActionMap.h>
#include <Building.h>
#include <GroundUnit.h>

using namespace StiGame;

const int AssetManager::BINDINGS_COUNT = 9;

AssetManager::AssetManager()
{
    //ctor
    loadData();
}

AssetManager::~AssetManager()
{
    //dtor
    delete resMetal;
    delete resGaz;
    delete bindings;
}

StiGame::ActionBinding* AssetManager::getBindings(void)
{
    return bindings;
}

std::list<std::string> AssetManager::getTextures(void)
{
    std::list< std::string > textures;
    //tiles
    textures.push_back(tileNormal);
    textures.push_back(tileBlock);

    //resources
    textures.push_back(resMetal->getTexture());
    textures.push_back(resGaz->getTexture());
    //base sprites

    textures.push_back(base->getPlacedSprite());
    textures.push_back(base->getConstructSprite(PC_Blue));
    textures.push_back(base->getSpriteName(PC_Blue));

    textures.push_back(base->getConstructSprite(PC_Red));
    textures.push_back(base->getSpriteName(PC_Red));

    //barrack sprites
    textures.push_back(barrack->getPlacedSprite());
    textures.push_back(barrack->getConstructSprite(PC_Blue));
    textures.push_back(barrack->getSpriteName(PC_Blue));

    textures.push_back(barrack->getConstructSprite(PC_Red));
    textures.push_back(barrack->getSpriteName(PC_Red));

    textures.push_back(house->getPlacedSprite());
    textures.push_back(house->getConstructSprite(PC_Blue));
    textures.push_back(house->getSpriteName(PC_Blue));

    textures.push_back(house->getConstructSprite(PC_Red));
    textures.push_back(house->getSpriteName(PC_Red));

    //textures.push_back(worker->getSprite(PC_Red, GUS_Idle));
    //textures.push_back(worker->getSprite(PC_Blue, GUS_Idle));

    //house to add

    return textures;
}

std::list<std::string> AssetManager::getDirectionSprites(void)
{
    std::list< std::string > dsprites;

    dsprites.push_back(worker->getSprite(PC_Blue, GUS_Moving));
    dsprites.push_back(worker->getSprite(PC_Red, GUS_Moving));

    dsprites.push_back(melee->getSprite(PC_Blue, GUS_Moving));
    dsprites.push_back(melee->getSprite(PC_Red, GUS_Moving));

    return dsprites;
}

BuildingIdentity* AssetManager::getBaseIdentity()
{
    return base;
}

ResourceIdentity* AssetManager::getMetalIdentity(void)
{
    return resMetal;
}

ResourceIdentity* AssetManager::getGazIdentity(void)
{
    return resGaz;
}

std::string AssetManager::getTileNormal(void)
{
    return tileNormal;
}

std::string AssetManager::getTileBlock(void)
{
    return tileBlock;
}

GroundUnitIdentity* AssetManager::getWorkerIdentity()
{
    return worker;
}

GroundUnitIdentity* AssetManager::getMeleeIdentity(void)
{
    return melee;
}

BuildingIdentity* AssetManager::getBarrackIdentity(void)
{
    return barrack;
}

BuildingIdentity* AssetManager::getHouseIdentity(void)
{
    return house;
}

void AssetManager::initBindings()
{
    KeyActionMap *kmap;
    kmap = new KeyActionMap("view_move_up", SDLK_UP);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("view_move_down", SDLK_DOWN);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("view_move_left", SDLK_LEFT);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("view_move_right", SDLK_RIGHT);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("show_minimap", SDLK_m);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("show_minimap", SDLK_m);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("show_fps", SDLK_f);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("toggle_console", SDLK_c);
    bindings->addBinding(kmap);

    kmap = new KeyActionMap("pause_game", SDLK_PAUSE);
    bindings->addBinding(kmap);
}

void AssetManager::loadData(void)
{
    std::string p = GamePath::getFilepath(AssetRoot, "assets.def");
    VarFile vf (p.c_str());
    vf.read();
    std::string rmetal = vf.getValue("res_metal");
    std::string rgaz = vf.getValue("res_gaz");

    tileNormal = vf.getValue("tile_normal");
    tileBlock = vf.getValue("tile_block");

    //loading VFResource
    resMetal = new ResourceIdentity(rmetal);
    resGaz = new ResourceIdentity(rgaz);

    std::string rbase = vf.getValue("base_building");

    p = GamePath::getFilepath(AssetRoot, rbase);
    base = new BuildingIdentity(BT_Base , p);

    std::string rbarrack = vf.getValue("barrack_building");
    p = GamePath::getFilepath(AssetRoot, rbarrack);
    barrack = new BuildingIdentity(BT_Barrack, p);

    std::string rhouse = vf.getValue("house_building");
    p = GamePath::getFilepath(AssetRoot, rhouse);
    house = new BuildingIdentity(BT_House, p);

    std::string rworker = vf.getValue("worker");
    p = GamePath::getFilepath(AssetRoot, rworker);
    worker = new GroundUnitIdentity(p);

    std::string rmelee = vf.getValue("melee");
    p = GamePath::getFilepath(AssetRoot, rmelee);
    melee = new GroundUnitIdentity(p);

    harvestSpeed = vf.getInt("harvestSpeed");
    buildSpeed = vf.getInt("buildSpeed");

    p = GamePath::getFilepath(AssetRoot, "bindings.cfg");
    bindings = new ActionBinding(p);
    bindings->read();

    if(bindings->getCount() < BINDINGS_COUNT)
    {
        initBindings();
        bindings->write();
    }

}

int AssetManager::getHarvestSpeed()
{
    return harvestSpeed;
}

int AssetManager::getBuildSpeed()
{
    return buildSpeed;
}
