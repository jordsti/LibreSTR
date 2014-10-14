#ifndef TOPHUD_H
#define TOPHUD_H

#include <Item.h>
#include <Label.h>
#include <Image.h>
#include <list>
#include "Player.h"

#include "AssetManager.h"
class TopHud :
    public StiGame::Gui::Item
{
public:
    TopHud(AssetManager *m_assets, Player *m_player);
    virtual ~TopHud();

    StiGame::Surface* render(void);

protected:
    void updateHud(void);
    void renderBackground(void);
    void resized(void);
private:
    Player *player;
    AssetManager *assets;
    StiGame::Gui::Image iconMetal;
    StiGame::Gui::Image iconGaz;
    StiGame::Gui::Label lblMetalCount;
    StiGame::Gui::Label lblGazCount;
    StiGame::Color textColor;
    std::list<StiGame::Gui::Item*> items;
    StiGame::Surface *leftImage;
    StiGame::Surface *bgImage;
    StiGame::Surface *rightImage;
    StiGame::Surface *bg;
};

#endif // TOPHUD_H
