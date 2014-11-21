#ifndef PLAYERMAP_H
#define PLAYERMAP_H
#include "ITileMap.h"
#include <vector>
#include <Point.h>


class PlayerMap :
        public ITileMap
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

        int getDefaultTextureId(void);
        std::string getDefaultTexture(void);
        std::string getTexture(int id);
        int getTextureCount(void);

        void addTexture(std::string m_texture);
        void setDefaultTextureId(int m_defaultTexture);

        int getBuildingsCount(void);
        Building* getBuilding(int index);
        void addBuilding(Building *m_building);

        int getGroundUnitsCount(void);
        GroundUnit* getGroundUnit(int index);
        void addGroundUnit(GroundUnit *m_unit);

        bool containsBuilding(Building *building);
        bool containsGroundUnit(GroundUnit *unit);

    protected:
    private:
        void initRows(void);
        int width;
        int height;
        int defaultTexture;
        std::vector< std::vector<Tile*> > tiles;
        std::vector<Tile*> tileRefs;
        std::vector<Resource*> resRefs;
        std::vector<std::string> textures;
        std::vector<Building*> buildings;
        std::vector<GroundUnit*> units;
};

#endif // PLAYERMAP_H
