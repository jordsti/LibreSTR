#include "AssetManager.h"
#include <VarFile.h>
#include <GamePath.h>

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

VFResource* AssetManager::getMetalDef(void)
{
    return resMetal;
}

VFResource* AssetManager::getGazDef(void)
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

void AssetManager::loadData(void)
{
    VarFile vf (GamePath::getFilepath(AssetRoot, "assets.def").c_str());
    vf.read();
    std::string rmetal = vf.getValue("res_metal");
    std::string rgaz = vf.getValue("res_gaz");

    tileNormal = vf.getValue("tile_normal");
    tileBlock = vf.getValue("tile_block");

    //loading VFResource
    resMetal = new VFResource(rmetal);
    resGaz = new VFResource(rgaz);

}
