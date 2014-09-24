#ifndef TILE_H
#define TILE_H

#include <string>

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
        virtual ~Tile();

        TileType getType(void);
        std::string getTexture(void);

        void setType(TileType m_type);
        void setTexture(std::string m_texture);

    protected:
        TileType type;
        std::string texture;
        //ressource
    private:
};

#endif // TILE_H
