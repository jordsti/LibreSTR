#ifndef TILE_H
#define TILE_H

#include <string>
#include "Resource.h"

enum TileType {
    TT_Normal,
    TT_Water,
    TT_Block
};

class Tile
{
    public:
        static const int TILE_WIDTH;
        static const int TILE_HEIGHT;

        Tile();
        Tile(TileType m_type, std::string m_texture);
        Tile(TileType m_type, std::string m_texture, int m_id);
        virtual ~Tile();

        int getId(void);

        TileType getType(void);
        std::string getTexture(void);
        Resource* getResource(void);
        bool containsResource(void);

        void setType(TileType m_type);
        void setTexture(std::string m_texture);
        void setResource(Resource *m_resource);

        Tile* clone(void);

    protected:
        TileType type;
        std::string texture;
        Resource *resource;
    private:
        int _id;
        static int GetCurrentId(void);
        static int _currentId;
};

#endif // TILE_H
