#include "RadialItem.h"

RadialItem::RadialItem(std::string m_name, std::string m_icon, std::string m_iconHover)
{
    name = m_name;
    icon = m_icon;
    iconHover = m_iconHover;
}

RadialItem::~RadialItem()
{

}

std::string RadialItem::getName(void)
{
    return name;
}

std::string RadialItem::getIcon(void)
{
    return icon;
}

std::string RadialItem::getIconHover(void)
{
    return iconHover;
}
