#ifndef UNITINFOPANEL_H
#define UNITINFOPANEL_H

#include <Item.h>
#include <Label.h>
#include <ImageButton.h>
#include "AssetManager.h"
#include "Unit.h"
#include "BuildingIdentity.h"

class GameState;

class UnitInfoPanel :
        public StiGame::Gui::Item
{
public:
    UnitInfoPanel();
    virtual ~UnitInfoPanel();

    void loadAssets(AssetManager *m_assets);
    void setGameState(GameState *m_state);

    StiGame::Surface* render(void);

    void onClick(StiGame::Point *relp);

    void setUnit(Unit *m_unit);
    Unit* getUnit(void);
protected:
   void updateInfo(void);

private:
    AssetManager *assets;
    GameState *state;
    Unit *unit;

    BuildingIdentity *baseBuilding;
    BuildingIdentity *barrackBuilding;
    BuildingIdentity *houseBuilding;

    StiGame::Surface *baseIcon;
    StiGame::Surface *barrackIcon;
    StiGame::Surface *houseIcon;

    StiGame::Gui::ImageButton btnBase;
    StiGame::Gui::ImageButton btnBarrack;
    StiGame::Gui::ImageButton btnHouse;

    StiGame::Color transparentBackground;
    StiGame::Gui::Label lblName;
    StiGame::Gui::Label lblType;
    StiGame::Gui::Label lblHealth;
    StiGame::Gui::Label lblInfo;

    std::vector< StiGame::Gui::Item* > _items;
};

#endif // UNITINFOPANEL_H
