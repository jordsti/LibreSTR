#include <Viewport.h>
#include <iostream>
#include "MapEditMainMenu.h"
using namespace StiGame;

int main(int argc, char **argv)
{
    int width = 1024;
    int height = 768;

    Dimension maxDim = Viewport::GetHighestResolution();

    width = maxDim.getWidth();
    height = maxDim.getHeight();

    std::cout << "Max resolution is " << width << "x" << height << std::endl;

    //this is in window mode, so we resize

    width -= 60;
    height -= 100;

    Viewport *vp = new Viewport(width, height, false);
    vp->setTitle("LibreSTR - MapEditor");

    MapEditMainMenu *menu = new MapEditMainMenu();
    vp->push(menu);


    vp->startLoop();

    return 0;
}
