#ifndef MAPITEM_H
#define MAPITEM_H
#include <Item.h>
#include <SpriteLibrary.h>
#include "MEMap.h"
class MapItem :
        public StiGame::Gui::Item
{
public:
    MapItem(MEMap *m_map, StiGame::SpriteLibrary *m_sprites, std::string m_defaultTexture);
    virtual ~MapItem();

    StiGame::Surface* render(void);
    void moveView(int d_x, int d_y);

    StiGame::Point* getPosition(void);

    void setSelectRectangle(int r_x, int r_y, int r_width, int r_height);
    void setSelectRectangleSize(int m_width, int m_height);

protected:
    MEMap *map;
    StiGame::SpriteLibrary *sprites;
    MPoint viewPoint;
    std::string defaultTexture;
    StiGame::Color selectColor;
    StiGame::Color borderSelectColor;
    StiGame::Rectangle selectRectangle;
};

#endif // MAPITEM_H
