
#include <Viewport.h>
#include <Runtime.h>
#include "MainMenu.h"
#include <iostream>
#include "LibreSTRStyle.h"
#include "MapGenerator.h"
#include "AssetManager.h"
#include "LibreSTRVersion.h"

#include "FileSystem.h"
#include "GameServer.h"

using namespace StiGame;

int main(int argc, char** argv)
{
    // this is the normal behaviour
    bool fullscreen = true;
    int width = 1024;
    int height = 768;
    bool serverMode = false;

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

    //switch override default behaviour

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
                std::cout << "Starting in window mode" << std::endl;
            }
            else if(arg == "-width")
            {
                if(i+1 < argc)
                {
                    i++;
                    std::string istr = argv[i];
                    width = atoi(istr.c_str());
                    std::cout << "Viewport width : " << width << std::endl;
                }
            }
            else if(arg == "-height")
            {
                if(i+1 < argc)
                {
                    i++;
                    std::string istr = argv[i];
                    height = atoi(istr.c_str());
                    std::cout << "Viewport height : " << height << std::endl;
                }
            }
            else if(arg == "-server")
            {
                serverMode = true;
            }
        }

        i++;
    }

    LibreSTRVersion version = LibreSTRVersion::CurrentVersion();
    if(serverMode)
    {
        GameServer server("default name");
        server.start();
    }
    else
    {
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
    }

    return 0;
}
