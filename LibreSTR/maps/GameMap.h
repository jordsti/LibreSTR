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
#include "MBuilding.h"
#include "MGroundUnit.h"

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

        bool placeBuilding(MBuilding *building, int t_x, int t_y);
        void forcePlaceBuilding(MBuilding *building, int t_x, int t_y);
        int getBuildingsCount(void);
        MBuilding* getBuilding(int index);
        MBuilding* getBuildingById(int id);
        void tickUnits(int ms);

        int getGroundUnitsCount(void);
        MGroundUnit* getGroundUnit(int index);
        bool placeGroundUnit(MGroundUnit *unit, int pt_x, int pt_y);

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

        std::vector< MBuilding* > buildings;
        std::vector< MGroundUnit* > units;

        std::vector< std::vector<Tile*> > tiles;

        std::map<int, std::vector<StiGame::Point>> startingPoints;

        std::vector< std::string > textures;

    private:
};

#endif // MAP_H
