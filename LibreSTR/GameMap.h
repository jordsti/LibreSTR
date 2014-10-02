#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <Point.h>
#include "Tile.h"
#include <vector>
#include <map>
#include <iostream>
#include "PlayerMap.h"
#include "AssetManager.h"

struct MapHeader
{
    int width;
    int height;
    int seed;
};

struct TileInfo
{
    int type;
};

struct ResourceMarker
{
    int count;
};

struct ResourceInfo
{
    int x;
    int y;
    int amount;
    int type;
};

class GameMap
{
    public:
        static const int PLAYERS_MAX;
        GameMap();
        GameMap(int m_width, int m_height);
        GameMap(int m_width, int m_height, int m_seed);
        virtual ~GameMap();

        int getWidth(void);
        int getHeight(void);
        int getSeed(void);

        Tile* get(int x, int y);

        bool contains(int x, int y);
        bool contains(StiGame::Point& pt);

        void addStartPoint(int player, StiGame::Point& pt);

        PlayerMap* GeneratePlayerMap(int playerId);

        void save(std::string output);
        void load(std::string input, AssetManager *asset);

    protected:
        void initTiles(void);
        void initPtsMap(void);

        int width;
        int height;
        int seed;
        std::vector< std::vector<Tile*> > tiles;

        std::map<int, std::vector<StiGame::Point>> startingPoints;

    private:
};

#endif // MAP_H
