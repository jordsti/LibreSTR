#ifndef RADIALMENU_H
#define RADIALMENU_H
#include <Item.h>
#include <Font.h>
#include <vector>
#include "RadialItem.h"

class RadialMenu :
        StiGame::Gui::Item
{
public:
    static const int DEFAULT_RADIUS;

    RadialMenu();
    virtual ~RadialMenu();

    void setFont(StiGame::Font *m_font);
    void addItem(RadialItem *m_item);
    int count(void);

    int getRadius(void);
    void setRadius(int m_radius);

    RadialItem* getItem(int index);

    StiGame::Surface* render(void);
private:
    StiGame::Color transparentBackground;
    StiGame::Font *font;
    std::vector< RadialItem* > items;
    std::vector< StiGame::Surface* > icons;
    std::vector< StiGame::Surface* > iconsHover;
    int radius;
};

#endif // RADIALMENU_H
