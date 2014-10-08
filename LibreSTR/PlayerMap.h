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
};

#endif // PLAYERMAP_H
