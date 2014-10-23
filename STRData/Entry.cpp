#include "Entry.h"
namespace FS
{
Entry::Entry()
{
    name = "";
    parent = "";
}


Entry::~Entry()
{

}

bool Entry::endsWith(std::string m_suffix)
{
    if(m_suffix.size() < name.size())
    {
        std::string n_suffix = name.substr(name.size() - m_suffix.size(), m_suffix.size());
        return (n_suffix == m_suffix);
    }
    else
    {
        return false;
    }
}

std::string Entry::getName(void)
{
    return name;
}

std::string Entry::getParent(void)
{
    return parent;
}

std::string Entry::getPath(void)
{
    if(parent.size() == 0)
    {
        return name;
    }

    return parent+"/"+name;
}

}
