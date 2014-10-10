#include "MiniMap.h"
#include <PRect.h>
#include <GamePath.h>
#include "GameState.h"
#include <iostream>

using namespace StiGame;

//todo
//add a bar with a hide button

MiniMap::MiniMap(GameState *m_state, ITileMap *m_playerMap, int m_width, int m_height, int m_borderWidth)
{
    state = m_state;
    playerMap = m_playerMap;
    width = m_width;
    height = m_height;
    borderWidth = m_borderWidth;

    closedImage = new Surface(GamePath::getFilepath(AssetRoot, "radar_icon.png"));
    closeIcon = new Surface(GamePath::getFilepath(AssetRoot, "close_icon.png"));

    miniTileWidth = (float)width / (float)playerMap->getWidth();
    miniTileHeight = (float)height / (float)playerMap->getHeight();

    viewWidth = 0;
    viewHeight = 0;
    viewX = 0;
    viewY = 0;

    background.setRGB(0, 0, 0);
    normalTile.setRGB(35, 35, 35);
    blockTile.setRGB(200, 10, 10);
    metalRes.setRGB(220, 220, 220);
    gazRes.setRGB(10, 230, 10);

    viewColor.setRGB(255, 255, 255);

    minimap = nullptr;
    hide = true;
    render();
}



bool MiniMap::isHide(void)
{
    return hide;
}

void MiniMap::setHide(bool m_hide)
{
    hide = m_hide;
}

MiniMap::~MiniMap()
{
    if(minimap != nullptr)
    {
        delete minimap;
    }

    delete closedImage;
    delete closeIcon;
}

void MiniMap::setViewPoint(int m_x, int m_y)
{
    if(m_x != viewX || m_y != viewY)
    {
        viewX = m_x;
        viewY = m_y;
        render();
    }
}

Dimension MiniMap::getDimension(void)
{
    if(hide)
        return Dimension(closedImage->getWidth(), closedImage->getHeight());
    else
        return Dimension(minimap->getWidth(), minimap->getHeight());
}


void MiniMap::mouseClick(StiGame::Point& pt)
{
    if(hide)
    {
        hide = false;
    }
    else
    {
        Rectangle mapZone (0, 0, width, height);
        Rectangle zone (width + (borderWidth - closeIcon->getWidth())/2, 0, closeIcon->getWidth(), closeIcon->getHeight());
        if(zone.contains(&pt))
        {
            hide = true;
        }
        else if(mapZone.contains(&pt))
        {
            int n_x = 0;
            int n_y = 0;

            n_x = pt.getX() / (int)miniTileWidth;
            n_y = pt.getY() / (int)miniTileHeight;

            n_x -= (viewWidth/Tile::TILE_WIDTH)/2;
            n_y -= (viewHeight/Tile::TILE_HEIGHT)/2;

            if(n_x < 0)
                n_x = 0;

            if(n_y < 0)
                n_y = 0;

            if(n_x > playerMap->getWidth() - (viewWidth/Tile::TILE_WIDTH))
                n_x = playerMap->getWidth() - (viewWidth/Tile::TILE_WIDTH);

            if(n_y > playerMap->getHeight() - (viewHeight/Tile::TILE_HEIGHT))
                n_y = playerMap->getHeight() - (viewHeight/Tile::TILE_HEIGHT);

            state->setViewPoint(n_x, n_y);
            viewX = n_x * Tile::TILE_WIDTH;
            viewY = n_y * Tile::TILE_HEIGHT;

            render();
        }
    }

}

void MiniMap::setViewDimension(int m_viewWidth, int m_viewHeight)
{
    if(viewWidth != m_viewWidth || viewHeight != m_viewHeight)
    {
        viewWidth = m_viewWidth;
        viewHeight = m_viewHeight;
        render();
    }
}

Surface* MiniMap::getSurface(void)
{
    if(hide)
    {
        Surface *nsur = new Surface(closedImage->getSDLSurface());
        nsur->setReleaseSurface(false);
        return nsur;
    }
    else
    {
        Surface *nsur = new Surface(minimap->getSDLSurface());
        nsur->setReleaseSurface(false);
        return nsur;
    }
}

void MiniMap::render(void)
{
    if(minimap != nullptr)
    {
        delete minimap;
    }

    minimap = new Surface(width + borderWidth, height);
    minimap->fill(&background);


    SDL_Rect rect;
    rect.w = miniTileWidth;
    rect.h = miniTileHeight;

    for(int y=0; y<playerMap->getHeight(); y++)
    {
        for(int x=0; x<playerMap->getWidth(); x++)
        {
            Tile *t = playerMap->get(x, y);
            rect.x = (float)x * miniTileWidth;
            rect.y = (float)y * miniTileHeight;


            if(t->containsResource())
            {
                if(t->getResource()->getType() == RT_METAL)
                {
                    minimap->fillRect(&rect, &metalRes);
                }
                else if(t->getResource()->getType() == RT_GAZ)
                {
                    minimap->fillRect(&rect, &gazRes);
                }
            }
            else if(t->getType() == TT_Normal)
            {
                minimap->fillRect(&rect, &normalTile);
            }
            else if(t->getType() == TT_Normal)
            {
                minimap->fillRect(&rect, &blockTile);
            }
        }
    }

    //drawing view rect
    PRect viewRect ((viewX/Tile::TILE_WIDTH)*miniTileWidth,
                    (viewY/Tile::TILE_HEIGHT)*miniTileHeight,
                    (viewWidth/Tile::TILE_WIDTH)*miniTileWidth,
                    (viewHeight/Tile::TILE_HEIGHT)*miniTileHeight);


    minimap->draw(&viewRect, &viewColor);

    //close icon

    Point cpt (width + (borderWidth - closeIcon->getWidth())/2, 0);

    minimap->blit(closeIcon, &cpt);

}

int MiniMap::getWidth(void)
{
    if(hide)
        return closedImage->getWidth();

    return width;
}

int MiniMap::getHeight(void)
{
    if(hide)
        return closedImage->getHeight();

    return height;
}
