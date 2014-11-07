#ifndef RADIALMENU_H
#define RADIALMENU_H
#include <Item.h>
#include <Font.h>
#include <vector>
#include "RadialItem.h"
#include <StringRenderer.h>

struct ItemSurface {
    StiGame::Surface *normal;
    StiGame::Surface *hover;
};

class RadialMenu :
        public StiGame::Gui::Item
{
public:
    static const int DEFAULT_RADIUS;
    static const int DEFAULT_DEGREE_OFFSET;

    RadialMenu();
    virtual ~RadialMenu();

    void setFont(StiGame::Font *m_font);
    void addItem(RadialItem *m_item);
    int count(void);

    int getRadius(void);
    void setRadius(int m_radius);

    int getDegreeOffset(void);
    void setDegreeOffset(int m_degreeOffset);

    std::string getCaption(void);
    void setCaption(std::string m_caption);

    RadialItem* getItem(int index);

    StiGame::Surface* render(void);

    void setCloseIcon(std::string iconPath);

protected:
    void renderCaption(void);

private:
    StiGame::Surface *closeIcon;
    StiGame::StringRenderer renderer;
    std::string caption;
    StiGame::Color transparentBackground;
    StiGame::Font *font;
    std::vector< RadialItem* > items;
    std::vector< ItemSurface* > icons;
    int radius;
    int degreeOffset;
};

#endif // RADIALMENU_H
