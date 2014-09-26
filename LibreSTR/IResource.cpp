#include "IResource.h"

int IResource::_currentId = 0;

IResource::IResource()
{
    //ctor
    name = "IResource";
    texture = "nothing";
    amount = 0;
    type = RT_NOT_DEFINED;

    _id = GetCurrendId();

}

IResource::IResource(int m_id)
{
    //ctor
    name = "IResource";
    texture = "nothing";
    amount = 0;
    type = RT_NOT_DEFINED;

    _id = m_id;

}

IResource::~IResource()
{
    //dtor
}

int IResource::getId(void)
{
    return _id;
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

int IResource::GetCurrendId(void)
{
    int id = _currentId;
    _currentId++;
    return id;
}
