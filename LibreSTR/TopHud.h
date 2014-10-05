#ifndef TOPHUD_H
#define TOPHUD_H

#include <Item.h>
#include <Label.h>
#include <Image.h>
#include <list>

#include "AssetManager.h"
class TopHud :
    public StiGame::Gui::Item
{
public:
    TopHud(AssetManager *m_assets);
    virtual ~TopHud();

    StiGame::Surface* render(void);
private:
    AssetManager *assets;
    StiGame::Gui::Image iconMetal;
    StiGame::Gui::Image iconGaz;
    StiGame::Gui::Label lblMetalCount;
    StiGame::Gui::Label lblGazCount;
    StiGame::Color textColor;
    std::list<StiGame::Gui::Item*> items;
};

#endif // TOPHUD_H
