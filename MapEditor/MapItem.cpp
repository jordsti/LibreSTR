#include "MapItem.h"
#include "PRect.h"
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
    selectColor.setRGBA(0, 0, 200, 150);
    borderSelectColor.setRGB(0, 0, 200);
}

MapItem::~MapItem()
{

}

void MapItem::setSelectRectangle(int r_x, int r_y, int r_width, int r_height)
{
    if(r_x < map->getWidth() &&
            r_y < map->getHeight() &&
            r_x + r_width < map->getWidth() &&
            r_y + r_height < map->getHeight() &&
            r_x >= 0 &&
            r_y >= 0)
    {
        selectRectangle.setRectangle(r_x, r_y, r_width, r_height);
    }
}

void MapItem::setSelectRectangleSize(int m_width, int m_height)
{
    setSelectRectangle(selectRectangle.getX(), selectRectangle.getY(), m_width, m_height);
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

    if(selectRectangle.getWidth() > 0 && selectRectangle.getHeight() > 0)
    {
        Surface rectSur = Surface(selectRectangle.getWidth() * map->getTileDimension()->getWidth(), selectRectangle.getHeight() * map->getTileDimension()->getHeight());
        rectSur.fill(&selectColor);
        //to add into stigame
        rectSur.setBlendMode(SDL_BLENDMODE_ADD);
        Point pt ((selectRectangle.getX() * map->getTileDimension()->getWidth()) - viewPoint.getX() * map->getTileDimension()->getWidth(),
                  (selectRectangle.getY() * map->getTileDimension()->getHeight()) - viewPoint.getY()* map->getTileDimension()->getHeight());

        PRect border (pt.getX(), pt.getY(), selectRectangle.getWidth() * map->getTileDimension()->getWidth(), selectRectangle.getHeight() * map->getTileDimension()->getHeight());

        buffer->blit(&rectSur, &pt);
        buffer->draw(&border, &borderSelectColor);

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

