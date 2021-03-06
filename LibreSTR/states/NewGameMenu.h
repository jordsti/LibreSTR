#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H

#include <GuiState.h>
#include <Button.h>
#include <Label.h>
#include <ComboBox.h>
#include <EventListener.h>
#include <SelectionEventListener.h>
#include "AssetManager.h"

class NewGameMenu :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener,
        public StiGame::Gui::SelectionEventListener
{
public:
    NewGameMenu(AssetManager *m_assets);
    virtual ~NewGameMenu();

    void onStart(void);
    void onResize(int m_width, int m_height);

    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args);
    void handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *args);

protected:
    void initComponents();

    AssetManager *assets;

    StiGame::Gui::Button btnBack;
    StiGame::Gui::Button btnStart;

    StiGame::Gui::Label lblTitle;
    StiGame::Gui::Label lblMapSize;
    StiGame::Gui::Label lblPopSize;

    StiGame::Gui::ComboBox cbMapSize;
    StiGame::Gui::ComboBox cbPopSize;

    StiGame::Gui::ValueObject voSmall;
    StiGame::Gui::ValueObject voMedium;
    StiGame::Gui::ValueObject voLarge;

    StiGame::Gui::ValueObject voSmallPop;
    StiGame::Gui::ValueObject voMediumPop;
    StiGame::Gui::ValueObject voLargePop;
    StiGame::Gui::ValueObject voUnlimited;

    int smallPop;
    int mediumPop;
    int largePop;
    int unlimitedPop;

    int currentPopLimit;

    StiGame::Dimension dimSmall;
    StiGame::Dimension dimMedium;
    StiGame::Dimension dimLarge;

    StiGame::Dimension *currentDim;
};

#endif // NEWGAMEMENU_H
