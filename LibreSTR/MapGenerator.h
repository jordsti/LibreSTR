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

        static const int LIMIT_OFFSET;
        static const int MAX_ITERATION;
        static const int N_TILES;
        static const int METAL_TILES;
        static const int GAZ_TILES;
    protected:
        static void PlaceRessource(GameMap *gmap, int x, int y, int n, int metalTiles, int gazTiles);
    private:
};

#endif // MAPGENERATOR_H
