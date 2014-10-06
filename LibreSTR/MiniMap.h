#ifndef MINIMAP_H
#define MINIMAP_H

#include "PlayerMap.h"
#include <Surface.h>

class GameState;

class MiniMap
{
public:
    MiniMap(GameState *m_state, PlayerMap *m_playerMap, int m_width, int m_height, int m_borderWidth);

    virtual ~MiniMap();

    void setViewDimension(int m_viewWidth, int m_viewHeight);
    void setViewPoint(int m_x, int m_y);

    StiGame::Surface *getSurface(void);


    bool isHide(void);
    void setHide(bool m_hide);

    int getWidth(void);
    int getHeight(void);

    StiGame::Dimension getDimension(void);

    void mouseClick(StiGame::Point& pt);

private:
    bool hide;

    void render(void);
    PlayerMap *playerMap;
    float miniTileWidth;
    float miniTileHeight;
    int width;
    int height;

    int viewWidth;
    int viewHeight;
    int viewX;
    int viewY;
    int borderWidth;

    GameState *state;

    StiGame::Color viewColor;
    StiGame::Color background;
    StiGame::Color normalTile;
    StiGame::Color blockTile;
    StiGame::Color metalRes;
    StiGame::Color gazRes;
    StiGame::Surface *closeIcon;
    StiGame::Surface *minimap;
    StiGame::Surface *closedImage;

};

#endif // MINIMAP_H
