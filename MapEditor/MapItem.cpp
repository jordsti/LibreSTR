#include "MapItem.h"

using namespace StiGame;
using namespace Gui;

MapItem::MapItem(MEMap *m_map, StiGame::SpriteLibrary *m_sprites, std::string m_defaultTexture) : Item("MapItem")
{
    map = m_map;
    sprites = m_sprites;
    defaultTexture = m_defaultTexture;

    //in tiles !
    viewPoint.setPoint(0, 0);
    background = new Color(0, 0, 0);
}

MapItem::~MapItem()
{

}

StiGame::Surface* MapItem::render(void)
{
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);

    int s_x = viewPoint.getX();
    int s_y = viewPoint.getY();
    Dimension *tileDim = map->getTileDimension();

    int v_w = (width / tileDim->getWidth()) + 1;
    int v_h = (height / tileDim->getHeight()) + 1;

    MPoint drawPt;

    for(int y=0; y<v_h; y++)
    {
        if(y < map->getHeight())
        {
            for(int x=0; x<v_w; x++)
            {
                if(x < map->getWidth())
                {
                    METile *t = map->getTile(x, y);
                    Sprite *spr;
                    if(t->texture.size() > 0)
                    {
                        spr = sprites->getSprite(t->texture);
                    }
                    else
                    {
                        spr = sprites->getSprite(defaultTexture);
                    }

                    drawPt.setPoint(x * tileDim->getWidth(), y * tileDim->getHeight());
                    Surface *sprSur = spr->getCurrentSurface();
                    buffer->blit(sprSur, &drawPt);
                }
            }
        }
    }

    return buffer;
}

Point* MapItem::getPosition(void)
{
    return &viewPoint;
}

void MapItem::moveView(int d_x, int d_y)
{
    if(viewPoint.getX() + d_x < (map->getWidth() - (width/map->getTileDimension()->getWidth())) + 1 && viewPoint.getX() + d_x >= 0)
    {
        viewPoint.setX(viewPoint.getX() + d_x);
    }

    if(viewPoint.getY() + d_y < (map->getHeight() - (height/map->getTileDimension()->getHeight())) + 1 && viewPoint.getY() + d_y >= 0)
    {
        viewPoint.setY(viewPoint.getY() + d_y);
    }
}

