#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "GameMap.h"

class MapGenerator
{
    public:
        MapGenerator();
        virtual ~MapGenerator();
        static GameMap* RandomMap(int width, int height);
        static GameMap* RandomMap(int width, int height, int seed);
    protected:
    private:
};

#endif // MAPGENERATOR_H
