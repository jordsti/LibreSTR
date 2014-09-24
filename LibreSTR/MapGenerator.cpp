#include "MapGenerator.h"
#include "TimeTools.h"
#include <cstdlib>

MapGenerator::MapGenerator()
{
    //ctor
}

MapGenerator::~MapGenerator()
{
    //dtor
}

GameMap* MapGenerator::RandomMap(int width, int height)
{
    int seed = StiGame::Time::GenerateSeed();
    return RandomMap(width, height, seed);
}

GameMap* MapGenerator::RandomMap(int width, int height, int seed)
{
    srand(seed);
    GameMap *gmap = new GameMap(width, height, seed);

    for(int y=0; y<height; y++)
    {
        for(int x=0; x<width; x++)
        {
            Tile *t = gmap->get(x, y);

            int i = rand() % 10;

            if(i >= 0 || i <= 2)
            {
                t->setType(TT_Block);
            }
            /*else if(i < 5 && i > 2)
            {
                t->setType(TT_Water);
            }*/
        }
    }

    return gmap;
}
