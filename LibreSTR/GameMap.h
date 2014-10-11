#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <Point.h>
#include <vector>
#include <map>
#include <iostream>
#include "PlayerMap.h"
#include "AssetManager.h"
#include "ITileMap.h"
#include <MapData.h>

class GameMap :
        public ITileMap
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

        bool placeBuilding(Building *building, int t_x, int t_y);
        void forcePlaceBuilding(Building *building, int t_x, int t_y);
        int getBuildingsCount(void);
        Building* getBuilding(int index);


        int addTexture(std::string name);
        std::string getTexture(int id);

        int getDefaultTextureId(void);
        std::string getDefaultTexture(void);

        std::vector<StiGame::Point>& getPlayerStartingPoints(int index);


        int getTextureCount(void);
    protected:
        void initTiles(void);
        void initPtsMap(void);

        int width;
        int height;
        int seed;
        int defaultTexture;

        std::vector< Building* > buildings;

        std::vector< std::vector<Tile*> > tiles;

        std::map<int, std::vector<StiGame::Point>> startingPoints;

        std::vector< std::string > textures;

    private:
};

#endif // MAP_H
