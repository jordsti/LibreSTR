#include "AssetManager.h"
#include <VarFile.h>
#include <GamePath.h>
#include <KeyActionMap.h>

using namespace StiGame;

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

    textures.push_back(base->getPlacedSprite());
    textures.push_back(base->getConstructSprite(PC_Red));
    textures.push_back(base->getSpriteName(PC_Red));

    return textures;
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
    base = new BuildingIdentity(p);

    p = GamePath::getFilepath(AssetRoot, "bindings.cfg");
    bindings = new ActionBinding(p);
    bindings->read();

    if(bindings->getCount() < 6)
    {
        initBindings();
        bindings->write();
    }

}
