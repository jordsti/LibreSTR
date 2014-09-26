#include "IResource.h"

IResource::IResource()
{
    //ctor
    name = "IResource";
    texture = "nothing";
    amount = 0;
    type = RT_NOT_DEFINED;
}

IResource::~IResource()
{
    //dtor
}


std::string IResource::getName(void)
{
    return name;
}

std::string IResource::getTexture(void)
{
    return texture;
}

ResourceType IResource::getType(void)
{
        return type;
}

int IResource::getAmount(void)
{
    return amount;
}
