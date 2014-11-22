#ifndef MULTISELECTIONPANEL_H
#define MULTISELECTIONPANEL_H

#include <Item.h>
#include <vector>
#include <map>
#include "GroundUnit.h"
#include "AssetManager.h"
/*
 * Show all selected units into little square with hp
 * This is intended for ground units only !
 */

class MultiSelectionPanel :
        public StiGame::Gui::Item
{
public:
    MultiSelectionPanel();
    virtual ~MultiSelectionPanel();
    StiGame::Surface* render(void);

    void clearSelection(void);
    void addGroundUnit(GroundUnit *unit);

    void setAssets(AssetManager *m_assets);

private:
    std::vector<GroundUnit*> units;
    std::map<std::string, StiGame::Surface*> unitIcons;
    AssetManager *assets;
};

#endif // MULTISELECTIONPANEL_H
