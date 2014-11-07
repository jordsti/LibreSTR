#include "RadialMenu.h"
#include <MathTK.h>
#include <Angle.h>
#include <cmath>

const int RadialMenu::DEFAULT_RADIUS = 120;
const int RadialMenu::DEFAULT_DEGREE_OFFSET = 25;

using namespace StiGame;
using namespace Gui;

RadialMenu::RadialMenu() : Item("RadialMenu")
{
    radius = DEFAULT_RADIUS;
    font = style->getNormalFont();

    transparentBackground.setRGBA(0, 0, 0, 0);
    background = &transparentBackground;
    caption = "";
    degreeOffset = DEFAULT_DEGREE_OFFSET;
    renderer.setFont(font);
    closeIcon = nullptr;
}

RadialMenu::~RadialMenu()
{
    if(closeIcon != nullptr)
    {
        delete closeIcon;
    }

    auto vit(icons.begin()), vend(icons.end());
    for(;vit!=vend;++vit)
    {
        delete (*vit)->normal;
        delete (*vit)->hover;
        delete (*vit);
    }

    auto vit2(items.begin()), vend2(items.end());
    for(;vit2!=vend2;++vit2)
    {
        delete (*vit2);
    }
}

void RadialMenu::setCloseIcon(std::string iconPath)
{
    if(closeIcon != nullptr)
    {
        delete closeIcon;
    }

    closeIcon = new Surface(iconPath);
}

int RadialMenu::getDegreeOffset(void)
{
    return degreeOffset;
}

void RadialMenu::setDegreeOffset(int m_degreeOffset)
{
    degreeOffset = m_degreeOffset;
}

std::string RadialMenu::getCaption(void)
{
    return caption;
}

void RadialMenu::setCaption(std::string m_caption)
{
    caption = m_caption;
    renderer.setText(caption);
}

void RadialMenu::setFont(StiGame::Font *m_font)
{
    font = m_font;
    renderer.setFont(font);
}

void RadialMenu::addItem(RadialItem *m_item)
{
    items.push_back(m_item);

    ItemSurface *isurs = new ItemSurface();

    isurs->normal = new Surface(m_item->getIcon());
    isurs->hover = new Surface(m_item->getIconHover());

    icons.push_back(isurs);
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
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);
    //writing caption at the top
    Surface *surCaption = renderer.getSurface();

    MPoint dst ((width - surCaption->getWidth())/2, 5);
    buffer->blit(surCaption, &dst);

    //drawing each item
    auto vit(icons.begin()), vend(icons.end());
    int i=1;
    Math::Angle *angle =  Math::TK::CreateAngle(Math::AU_DEGREE, 0);

    for(;vit!=vend;++vit)
    {
        //30 degs by items
        angle->setAngle(i*degreeOffset);
        ItemSurface *surs = (*vit);
        int x = (int)((float)radius*cos(angle->getAngle(Math::AU_RADIAN))) + (width - surs->normal->getWidth())/2;
        int y = (int)((float)radius*sin(angle->getAngle(Math::AU_RADIAN)));

        dst.setPoint(x, y);
        //hover not handled at the moment

        buffer->blit(surs->normal, &dst);

        i++;
    }

    if(closeIcon != nullptr)
    {
        //drawing close icon
        //in the middle

        dst.setPoint((width - closeIcon->getWidth())/2, surCaption->getHeight() + 10);

        buffer->blit(closeIcon, &dst);
    }

    delete angle;
    return buffer;
}
