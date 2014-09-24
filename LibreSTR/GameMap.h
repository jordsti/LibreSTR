#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Tile.h"
#include <vector>

class GameMap
{
    public:
        GameMap();
        GameMap(int m_width, int m_height);
        GameMap(int m_width, int m_height, int m_seed);
        virtual ~GameMap();

        int getWidth(void);
        int getHeight(void);
        int getSeed(void);

        Tile* get(int x, int y);

    protected:
        void initTiles(void);

        int width;
        int height;
        int seed;
        std::vector< std::vector<Tile*> > tiles;
    private:
};

#endif // MAP_H
