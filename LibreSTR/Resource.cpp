#include "Resource.h"
#include "ResourceIdentity.h"

int Resource::_currentId = 0;

Resource::Resource(ResourceIdentity *m_identity)
{
    //ctor
    _identity = m_identity;
    amount = _identity->getStartingAmount();
    _id = GetCurrendId();

}

Resource::Resource(ResourceIdentity *m_identity, int m_id)
{
    //ctor
    _identity = m_identity;
    amount = m_identity->getStartingAmount();
    _id = m_id;

}


Resource::~Resource()
{
    //dtor
}

ResourceIdentity* Resource::getIdentity(void)
{
    return _identity;
}

Resource* Resource::clone()
{
    Resource *res = new Resource(_identity, _id);
    res->setAmount(amount);
    return res;
}

int Resource::getId(void)
{
    return _id;
}

std::string Resource::getName(void)
{
    return _identity->getName();
}

std::string Resource::getTexture(void)
{
    return _identity->getTexture();
}

ResourceType Resource::getType(void)
{
    return _identity->getType();
}

std::string Resource::getIcon(void)
{
    return _identity->getIcon();
}

int Resource::getAmount(void)
{
    return amount;
}

void Resource::setAmount(int m_amount)
{
    amount = m_amount;
}

int Resource::GetCurrendId(void)
{
    int id = _currentId;
    _currentId++;
    return id;
}
