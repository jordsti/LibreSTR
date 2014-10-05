#include "VFResource.h"
#include <VarFile.h>
#include <GamePath.h>

using namespace StiGame;

VFResource::VFResource(IResource *parent)
    : IResource()
{
    //ctor
    name = parent->getName();
    type = parent->getType();
    texture = parent->getTexture();
    amount = parent->getAmount();
}

VFResource::VFResource(int m_id, IResource *parent)
    : IResource(m_id)
{
    name = parent->getName();
    type = parent->getType();
    texture = parent->getTexture();
    amount = parent->getAmount();
}

VFResource::VFResource(std::string var_file)
    : IResource()
{
    fromVarFile(var_file);
}

VFResource::~VFResource()
{
    //dtor
}

void VFResource::fromVarFile(std::string var_file)
{
    VarFile vf (GamePath::getFilepath(AssetRoot, var_file).c_str());
    vf.read();

    name = vf.getValue("name");
    texture = vf.getValue("texture");
    amount = vf.getInt("starting_amount");
    icon = vf.getValue("icon");
    type = static_cast<ResourceType>(vf.getInt("type"));
}

IResource* VFResource::clone(void)
{
    return new VFResource(getId(), this);
}

IResource* VFResource::create(void)
{
    return new VFResource(this);
}
