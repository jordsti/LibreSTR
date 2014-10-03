#include "TopHud.h"

using namespace StiGame;
using namespace Gui;

TopHud::TopHud()
{
    lblMetalCount.setCaption("Metal : 0");
    lblGazCount.setCaption("Gaz : 0");

    lblMetalCount.setPoint(10, 2);

    maximumSize.setHeight(25);
    height = 25;

    lblGazCount.setPoint(200, 2);

    textColor.setRGB(255, 255, 255);

    lblMetalCount.setForeground(&textColor);
    lblGazCount.setForeground(&textColor);
}

TopHud::~TopHud()
{

}

Surface* TopHud::render(void)
{
    Surface *sur = new Surface(width, height);

    sur->fill(background);

    Surface *itemBuffer;

    //lbl Metal

    SDL_Rect dst;

    itemBuffer = lblMetalCount.render();
    dst.x = lblMetalCount.getX();
    dst.y = lblMetalCount.getY();
    dst.w = lblMetalCount.getWidth();
    dst.h = lblMetalCount.getHeight();

    sur->blit(itemBuffer, &dst);

    delete itemBuffer;


    itemBuffer = lblGazCount.render();
    dst.x = lblGazCount.getX();
    dst.y = lblGazCount.getY();
    dst.w = lblGazCount.getWidth();
    dst.h = lblGazCount.getHeight();

    sur->blit(itemBuffer, &dst);

    delete itemBuffer;

    return sur;
}
