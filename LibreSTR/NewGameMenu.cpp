#include "NewGameMenu.h"
#include "MainMenu.h"
#include "GameState.h"

using namespace StiGame;
using namespace Gui;

NewGameMenu::NewGameMenu(AssetManager *m_assets)
{
    dimSmall = Dimension(160, 100);
    dimMedium = Dimension(220, 130);
    dimLarge = Dimension(300, 200);
    currentDim = &dimSmall;

    assets = m_assets;

    initComponents();
}

NewGameMenu::~NewGameMenu()
{

}

void NewGameMenu::onStart(void)
{
    running = true;
}

void NewGameMenu::onResize(int m_width, int m_height)
{
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);
    btnStart.setPoint(m_width - btnStart.getWidth() - 10, m_height - btnStart.getHeight() - 8);

    lblMapSize.setPoint(16, 200);
    delete lblMapSize.render();
    cbMapSize.setPoint(lblMapSize.getX() + lblMapSize.getWidth() + 5, 200);

    lblTitle.setPoint(8, 16);

    GuiState::onResize(m_width, m_height);
}

bool NewGameMenu::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args)
{
    if(src == &btnStart)
    {
        //max pop to be added in the new game state
        //todo
        GameState *state = new GameState(assets, currentDim->getWidth(), currentDim->getHeight(), 200);
        viewport->push(state);
    }
    else if(src == &btnBack)
    {
        MainMenu *state = new MainMenu(assets);
        viewport->push(state);
    }

    return false;
}

void NewGameMenu::handleEvent(SelectionEventThrower *src, SelectionEventArgs *args)
{
    if(args->getSelection() == &voSmall)
    {
        currentDim = &dimSmall;
    }
    else if(args->getSelection() == &voMedium)
    {
        currentDim = &dimMedium;
    }
    else if(args->getSelection() == &voLarge)
    {
        currentDim = &dimLarge;
    }
}

void NewGameMenu::initComponents()
{
    voSmall = ValueObject(0, "Small");
    voMedium = ValueObject(1, "Medium");
    voLarge = ValueObject(2, "Large");

    btnBack.setCaption("Back");
    btnStart.setCaption("Start Game");

    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("New Game");

    lblMapSize.setCaption("Map Size :");

    cbMapSize.add(&voSmall);
    cbMapSize.add(&voMedium);
    cbMapSize.add(&voLarge);

    add(&btnBack);
    add(&btnStart);
    add(&lblTitle);
    add(&lblMapSize);
    add(&cbMapSize);

    cbMapSize.subscribe(this);
    btnBack.subscribe(this);
    btnStart.subscribe(this);
}
