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

    return textures;
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

    p = GamePath::getFilepath(AssetRoot, "bindings.cfg");
    bindings = new ActionBinding(p);
    bindings->read();

    if(bindings->getCount() == 0)
    {
        initBindings();
        bindings->write();
    }

}
