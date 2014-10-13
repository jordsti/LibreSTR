#include "ResourceIdentity.h"
#include <VarFile.h>
#include <GamePath.h>

using namespace StiGame;

ResourceIdentity::ResourceIdentity(std::string var_file)
{
    name = "noname";
    type = RT_NOT_DEFINED;
    texture = "none";
    icon = "none";
    startingAmount = 0;
    fromVarFile(var_file);
}

ResourceIdentity::~ResourceIdentity()
{
    //dtor
}

void ResourceIdentity::fromVarFile(std::string var_file)
{
    std::string p = GamePath::getFilepath(AssetRoot, var_file);
    VarFile vf (p.c_str());
    vf.read();

    name = vf.getValue("name");
    texture = vf.getValue("texture");
    startingAmount = vf.getInt("starting_amount");
    icon = vf.getValue("icon");
    type = static_cast<ResourceType>(vf.getInt("type"));
}


int ResourceIdentity::getStartingAmount(void)
{
    return startingAmount;
}

ResourceType ResourceIdentity::getType(void)
{
    return type;
}

std::string ResourceIdentity::getIcon(void)
{
    return icon;
}

std::string ResourceIdentity::getTexture(void)
{
    return texture;
}

std::string ResourceIdentity::getName(void)
{
    return name;
}

Resource* ResourceIdentity::create(void)
{
    return new Resource(this);
}
