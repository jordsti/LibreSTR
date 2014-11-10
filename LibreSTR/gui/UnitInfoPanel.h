#ifndef UNITINFOPANEL_H
#define UNITINFOPANEL_H

#include <Item.h>
#include <Label.h>
#include "Unit.h"

class UnitInfoPanel :
        public StiGame::Gui::Item
{
public:
    UnitInfoPanel();
    virtual ~UnitInfoPanel();

    StiGame::Surface* render(void);

    void setUnit(Unit *m_unit);
    Unit* getUnit(void);
protected:
   void updateInfo(void);

private:
    Unit *unit;
    StiGame::Color transparentBackground;
    StiGame::Gui::Label lblName;
    StiGame::Gui::Label lblType;
    StiGame::Gui::Label lblHealth;
};

#endif // UNITINFOPANEL_H
