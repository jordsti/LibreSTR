#include "UnitInfoPanel.h"
using namespace StiGame;
using namespace Gui;

UnitInfoPanel::UnitInfoPanel() : Item("UnitInfoPanel")
{
    unit = nullptr;
    width = 360;
    height = 100;
    transparentBackground.setRGBA(50, 50, 50, 150);
    background = &transparentBackground;

    lblName.setPoint(5, 10);
    lblType.setPoint(5, 30);
    lblHealth.setPoint(5, 50);
}

UnitInfoPanel::~UnitInfoPanel()
{

}

 void UnitInfoPanel::updateInfo(void)
 {
     if(unit != nullptr)
     {
        lblName.setCaption("Name: "+unit->getName());
        if(unit->getType() == UT_Building)
        {
            lblType.setCaption("Building");
        }
        else if(unit->getType() == UT_Ground)
        {
            lblType.setCaption("Ground Unit");
        }

        lblHealth.setCaption("Health: "+std::to_string(unit->getMaxHealth())+"/"+std::to_string(unit->getCurrentHealth()));
     }
 }

StiGame::Surface* UnitInfoPanel::render(void)
{
    //todo
    updateInfo();
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);

    Surface *lbl  = lblName.render();
    buffer->blit(lbl, &lblName);
    delete lbl;

    lbl = lblType.render();
    buffer->blit(lbl, &lblType);
    delete lbl;

    lbl = lblHealth.render();
    buffer->blit(lbl, &lblHealth);
    delete lbl;

    return buffer;
}

void UnitInfoPanel::setUnit(Unit *m_unit)
{
    unit = m_unit;
}

Unit* UnitInfoPanel::getUnit(void)
{
    return unit;
}
