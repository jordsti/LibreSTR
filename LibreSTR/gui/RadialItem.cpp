#include "RadialItem.h"

RadialItem::RadialItem(int m_id, std::string m_name, std::string m_icon, std::string m_iconHover) :
    StiGame::Gui::ValueObject(m_id, m_name)
{
    icon = m_icon;
    iconHover = m_iconHover;
}

RadialItem::~RadialItem()
{

}

std::string RadialItem::getIcon(void)
{
    return icon;
}

std::string RadialItem::getIconHover(void)
{
    return iconHover;
}
