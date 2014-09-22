
#include <Viewport.h>
#include "MainMenu.h"
#include <iostream>

using namespace StiGame;
int main(int argc, char** argv)
{
    // this is the normal behaviour
    bool fullscreen = true;
    int width = 1366;
    int height = 768;

    Dimension maxDim = Viewport::GetHighestResolution();

    width = maxDim.getWidth();
    height = maxDim.getHeight();

    std::cout << "Max resolution is " << width << "x" << height << std::endl;

#ifdef DEBUG

//we don't want to go in fullscreen in debug mode
fullscreen =  false;
width -= 100;
height -= 100;
std::cout << "Debugging mode is ON !" << std::endl;
std::cout << "Overriding fullscreen resolution to windowed : " << width << "x" << height << std::endl;
//reduce the resolution a bit

#endif // DEBUG

    Viewport *vp = new Viewport(width, height, fullscreen);

    vp->setTitle("LibreSTR [0.0.0]");

    MainMenu *mainMenu = new MainMenu();

    vp->push(mainMenu);
    vp->startLoop();

    return 0;
}
