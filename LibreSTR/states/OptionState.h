#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include <GuiState.h>
#include <TextBox.h>
#include <Label.h>
#include <Button.h>
#include <ComboBox.h>
#include <EventListener.h>
#include <CheckBox.h>
#include <KeyBind.h>
#include <SelectionEventListener.h>
#include "AssetManager.h"

class OptionState :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener,
        public StiGame::Gui::SelectionEventListener
{
public:
    OptionState(AssetManager *m_assets);
    virtual ~OptionState();

    void onResize(int m_width, int m_height);

    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt);
    void handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *evt);

private:
    AssetManager *assets;

    StiGame::Gui::Label lblTitle;
    StiGame::Gui::TextBox tbPlayerName;
    StiGame::Gui::Label lblPlayerName;

    StiGame::Gui::Label lblResolutions;
    StiGame::Gui::ComboBox cbResolutions;

    StiGame::Gui::CheckBox cbFullscreen;

    StiGame::Gui::Button btnBack;

    StiGame::Gui::Label lblMinimap;
    StiGame::Gui::KeyBind kbShowMinimap;

    StiGame::Gui::Label lblPauseGame;
    StiGame::Gui::KeyBind kbPauseGame;

    StiGame::Gui::Label lblMoveViewUp;
    StiGame::Gui::KeyBind kbMoveViewUp;

    StiGame::Gui::Label lblMoveViewDown;
    StiGame::Gui::KeyBind kbMoveViewDown;

    StiGame::Gui::Label lblMoveViewRight;
    StiGame::Gui::KeyBind kbMoveViewRight;

    StiGame::Gui::Label lblMoveViewLeft;
    StiGame::Gui::KeyBind kbMoveViewLeft;

    void initComponents(void);
};

#endif // OPTIONSTATE_H
