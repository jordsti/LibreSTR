
#include <Viewport.h>
#include <Runtime.h>
#include "MainMenu.h"
#include <iostream>
#include "LibreSTRStyle.h"
#include "MapGenerator.h"

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

    GameMap *gmap = MapGenerator::RandomMap(200, 300);

    for(int y=0; y<gmap->getHeight(); y++)
    {
        for(int x=0; x<gmap->getWidth(); x++)
        {
            Tile *t = gmap->get(x, y);
            if(t->getType() == TT_Normal)
            {
                std::cout << "n";
            }
            else if(t->getType() == TT_Water)
            {
                std::cout << "w";
            }
            else
            {
                std::cout << "b";
            }
        }
        std::cout << std::endl;
    }

    Viewport *vp = new Viewport(width, height, fullscreen);

    vp->setTitle("LibreSTR [0.0.0]");

    LibreSTRStyle *style = new LibreSTRStyle();
    Gui::Runtime::getInstance()->ForceStyle(style);

    MainMenu *mainMenu = new MainMenu();

    vp->push(mainMenu);
    vp->startLoop();

    return 0;
}
