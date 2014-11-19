#include "ErrorLabel.h"

const int ErrorLabel::TICK_MAX = 120;

using namespace StiGame;
using namespace Gui;

ErrorLabel::ErrorLabel() :
    Item("ErrorLabel")
{
    tickMax = TICK_MAX;
    tickCount = 0;
    caption = "";
    font = style->getBigFont();
    textColor.setRGB(255, 0, 0);
    foreground = &textColor;

    strBuffer.setColor(&textColor);
    strBuffer.setFont(font);
    strBuffer.setText(caption);
}

ErrorLabel::~ErrorLabel(void)
{

}

void ErrorLabel::setTickMax(int m_tickMax)
{
    tickMax = m_tickMax;
}

StiGame::Surface* ErrorLabel::render(void)
{
    //todo
    tickCount++;

    if(tickCount >= tickMax)
    {
        tickCount = 0;
        visible = false;
    }

    // TODO
    //add a cloned surface to stigame
    Surface *buffer = new Surface(strBuffer.getSurface()->getSDLSurface());
    return buffer;
}

void ErrorLabel::setCaption(std::string m_caption)
{
    caption = m_caption;
    strBuffer.setText(caption);

    width = strBuffer.getWidth();
    height = strBuffer.getHeight();
}

std::string ErrorLabel::getCaption(void)
{
    return caption;
}

void ErrorLabel::setFont(StiGame::Font *m_font)
{
    font = m_font;
    strBuffer.setFont(font);
}

