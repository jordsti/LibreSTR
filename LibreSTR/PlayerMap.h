#ifndef PLAYERMAP_H
#define PLAYERMAP_H
#include "Tile.h"
#include <vector>
#include <Point.h>


class PlayerMap
{
    public:
        PlayerMap(int m_width, int m_height);
        virtual ~PlayerMap();

        int getWidth(void);
        int getHeight(void);

        void addTile(int row, Tile *tile);
        Tile* get(int x, int y);
        Tile* get(int tileId);

        StiGame::Point getPosition(Tile *tile);

        Resource* getResource(int resId);

    protected:
    private:
        void initRows(void);
        int width;
        int height;
        std::vector< std::vector<Tile*> > tiles;
        std::vector<Tile*> tileRefs;
        std::vector<Resource*> resRefs;
};

#endif // PLAYERMAP_H
