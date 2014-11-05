#include "RadialMenu.h"

const int RadialMenu::DEFAULT_RADIUS = 60;

using namespace StiGame;
using namespace Gui;

RadialMenu::RadialMenu() : Item("RadialMenu")
{
    radius = DEFAULT_RADIUS;
    font = style->getNormalFont();

    transparentBackground.setRGBA(0, 0, 0, 0);
    background = &transparentBackground;
}

RadialMenu::~RadialMenu()
{

}

void RadialMenu::setFont(StiGame::Font *m_font)
{
    font = m_font;
}

void RadialMenu::addItem(RadialItem *m_item)
{
    items.push_back(m_item);
    //todo , image loading
}

int RadialMenu::count(void)
{
    return items.size();
}

int RadialMenu::getRadius(void)
{
    return radius;
}

void RadialMenu::setRadius(int m_radius)
{
    radius = m_radius;
}

RadialItem* RadialMenu::getItem(int index)
{
    return items[index];
}

StiGame::Surface* RadialMenu::render(void)
{
    return new Surface(width, height);
}
