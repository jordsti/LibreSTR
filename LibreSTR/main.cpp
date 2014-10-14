
#include <Viewport.h>
#include <Runtime.h>
#include "MainMenu.h"
#include <iostream>
#include "LibreSTRStyle.h"
#include "MapGenerator.h"
#include "AssetManager.h"
#include "LibreSTRVersion.h"

using namespace StiGame;

int main(int argc, char** argv)
{
    // this is the normal behaviour
    bool fullscreen = true;
    int width = 1024;
    int height = 768;

    Dimension maxDim = Viewport::GetHighestResolution();

    width = maxDim.getWidth();
    height = maxDim.getHeight();

    std::cout << "Max resolution is " << width << "x" << height << std::endl;


    //switch parsing
    int i = 0;
    while(i < argc)
    {
        std::string arg = argv[i];

        if(i==0)
        {
            //current path is this needed ? maybe
        }
        else
        {
            if(arg == "-w" || arg == "-windowed")
            {
                fullscreen = false;
            }
        }

        i++;
    }

#ifdef DEBUG

//we don't want to go in fullscreen in debug mode
fullscreen =  false;
width -= 100;
height -= 100;
std::cout << "Debugging mode is ON !" << std::endl;
std::cout << "Overriding fullscreen resolution to windowed : " << width << "x" << height << std::endl;
//reduce the resolution a bit

#endif // DEBUG
    /*GameMap *gmap = MapGenerator::RandomMap(480, 300);

    PlayerMap *pmap = gmap->GeneratePlayerMap(0);

    Point pt = pmap->getPosition( pmap->get(2000) );

    std::cout << "Pt : " << pt.getX() << ", " << pt.getY() << std::endl;*/

    /*for(int y=0; y<pmap->getHeight(); y++)
    {
        for(int x=0; x<pmap->getWidth(); x++)
        {
            Tile *t = pmap->get(x, y);
            if(t->getType() == TT_Normal)
            {
                std::cout << "n" << t->getId();

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
    }*/
    LibreSTRVersion version = LibreSTRVersion::CurrentVersion();
    Viewport *vp = new Viewport(width, height, fullscreen);
    std::string vstr = version.getVersionString();
    std::string wtitle = "LibreSTR ["+ vstr +"]";
    vp->setTitle(wtitle.c_str());

    //loading asset
    AssetManager *assets = new AssetManager();
    MapGenerator::setAssets(assets);

    LibreSTRStyle *style = new LibreSTRStyle();
    Gui::Runtime::getInstance()->ForceStyle(style);

    MainMenu *mainMenu = new MainMenu(assets);

    vp->push(mainMenu);
    vp->setFps(50);
    vp->startLoop();

    return 0;
}
