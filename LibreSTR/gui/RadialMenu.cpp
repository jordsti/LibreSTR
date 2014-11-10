#include "RadialMenu.h"
#include <MathTK.h>
#include <Angle.h>
#include <cmath>

#include <iostream>

const int RadialMenu::DEFAULT_RADIUS = 120;
const int RadialMenu::DEFAULT_DEGREE_OFFSET = 30;

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

void RadialMenu::onMouseMotion(StiGame::Point *relp)
{
    mousePoint.setPoint(relp);
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

void RadialMenu::onClick(StiGame::Point *relp)
{
    mousePoint.setPoint(relp);

    //close rectangle test before
    if(closeIcon != nullptr)
    {
        //drawing close icon
        //in the middle
        Rectangle closeRect ((width - closeIcon->getWidth())/2,
                             renderer.getHeight() + 10,
                             closeIcon->getWidth(),
                             closeIcon->getHeight());

        if(closeRect.contains(relp))
        {
            visible = false;
            return;
        }
    }

    auto vit(icons.begin()), vend(icons.end());
    int i=0;
    Math::Angle *angle =  Math::TK::CreateAngle(Math::AU_DEGREE, 0);
    Rectangle tRect;
    for(;vit!=vend;++vit)
    {
        angle->setAngle((i+1)*degreeOffset);
        ItemSurface *surs = (*vit);

        //center to center radius
        int _length = (int)Math::TK::Pythagoras(surs->normal->getWidth(), surs->normal->getHeight());
        int _radius = radius - (_length/2);

        int x = (int)((float)_radius * cos(angle->getAngle(Math::AU_RADIAN))) + (width/2 - _length/2);
        int y = (int)((float)_radius*sin(angle->getAngle(Math::AU_RADIAN)));

        tRect.setPoint(x, y);
        tRect.setDimension(surs->normal->getWidth(), surs->normal->getHeight());

        if(tRect.contains(relp))
        {
            //throw event
            RadialItem *item = items[i];
            SelectionEventArgs args (item);
            publish(this, &args);
        }

        //hover not handled at the moment
        i++;
    }
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
    Rectangle tRect;
    for(;vit!=vend;++vit)
    {
        angle->setAngle(i*degreeOffset);
        ItemSurface *surs = (*vit);

        //center to center radius
        int _length = (int)Math::TK::Pythagoras(surs->normal->getWidth(), surs->normal->getHeight());
        int _radius = radius - (_length/2);

        int x = (int)((float)_radius * cos(angle->getAngle(Math::AU_RADIAN))) + (width/2 - _length/2);
        int y = (int)((float)_radius*sin(angle->getAngle(Math::AU_RADIAN)));

        dst.setPoint(x, y);
        tRect.setPoint(&dst);
        tRect.setDimension(surs->normal->getWidth(), surs->normal->getHeight());

        if(tRect.contains(&mousePoint))
        {
            //mouse hover
            buffer->blit(surs->hover, &dst);
        }
        else
        {
            buffer->blit(surs->normal, &dst);
        }

        //hover not handled at the moment
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
