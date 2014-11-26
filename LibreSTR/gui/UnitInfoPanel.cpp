#include "UnitInfoPanel.h"
#include "Building.h"
#include "GroundUnit.h"
#include "GamePath.h"
#include "GameState.h"
using namespace StiGame;
using namespace Gui;

UnitInfoPanel::UnitInfoPanel() : Item("UnitInfoPanel")
{
    unit = nullptr;
    state = nullptr;
    width = 360;
    height = 100;
    transparentBackground.setRGBA(50, 50, 50, 150);
    background = &transparentBackground;

    lblName.setPoint(5, 10);
    lblType.setPoint(5, 30);
    lblHealth.setPoint(5, 50);
    lblInfo.setPoint(5, 70);
}

UnitInfoPanel::~UnitInfoPanel()
{

}

void UnitInfoPanel::loadAssets(AssetManager *m_assets)
{
    assets = m_assets;
    baseBuilding = assets->getBaseIdentity();

    baseIcon = new Surface(GamePath::getFilepath(AssetRoot, baseBuilding->getIcon()));

    btnBase.setImage(baseIcon);
    btnBase.setImageHover(baseIcon);
    btnBase.setDimension(baseIcon->getWidth(), baseIcon->getHeight());
    btnBase.setPoint(width-btnBase.getWidth()-5, 5);
}

void UnitInfoPanel::onClick(StiGame::Point *relp)
{
    if(btnBase.isVisible())
    {
        if(btnBase.contains(relp))
        {
            //building placement
            if(state != nullptr)
            {
                GroundUnit *gu = dynamic_cast<GroundUnit*>(unit);
                state->placeBuilding(gu, baseBuilding);
            }
        }
    }
}

 void UnitInfoPanel::updateInfo(void)
 {
     if(unit != nullptr)
     {
        lblName.setCaption("Name: "+unit->getName());
        if(unit->getType() == UT_Building)
        {
            lblType.setCaption("Building");
            btnBase.setVisible(false);
        }
        else if(unit->getType() == UT_Ground)
        {
            lblType.setCaption("Ground Unit");

            GroundUnit *gunit = dynamic_cast<GroundUnit*>(unit);
            if(gunit->isWorking())
            {
                Task *current = gunit->getTask();
                lblInfo.setCaption(current->getCaption());
            }
            else
            {
                lblInfo.setCaption("Idle");
            }

            if(gunit->getIdentity()->isCanBuild())
            {
                btnBase.setVisible(true);
            }
            else
            {
                btnBase.setVisible(false);
            }
        }

        lblHealth.setCaption("Health: "+std::to_string(unit->getMaxHealth())+"/"+std::to_string(unit->getCurrentHealth()));

        if(unit->getType() == UT_Building)
        {
            Building *b = dynamic_cast<Building*>(unit);
            Job *currentJob = b->getCurrentJob();
            if(currentJob != nullptr)
            {
                int pc = (int)(((float)currentJob->getTimeElapsed() / (float)currentJob->getTimeNeeded())*100.0f);
                int secNeeded = currentJob->getTimeNeeded() / 1000;
                lblInfo.setCaption("Job Progress : " + std::to_string(pc) + " % (" + std::to_string(secNeeded) + "sec)");
            }
            else
            {
                lblInfo.setCaption("Idle");
            }
        }
     }
 }

void UnitInfoPanel::setGameState(GameState *m_state)
{
    state = m_state;
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

    lbl = lblInfo.render();
    buffer->blit(lbl, &lblInfo);
    delete lbl;

    if(btnBase.isVisible())
    {
        lbl = btnBase.render();
        buffer->blit(lbl, &btnBase);
        delete lbl;
    }

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
