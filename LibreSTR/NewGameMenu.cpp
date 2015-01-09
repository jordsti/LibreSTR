#include "NewGameMenu.h"
#include "MainMenu.h"
#include "GameState.h"
#include "MapGenerator.h"

using namespace StiGame;
using namespace Gui;

NewGameMenu::NewGameMenu(AssetManager *m_assets)
{
    dimSmall = Dimension(160, 100);
    dimMedium = Dimension(220, 130);
    dimLarge = Dimension(300, 200);

    smallPop = 150;
    mediumPop = 250;
    largePop = 500;
    unlimitedPop = -1;

    currentPopLimit = smallPop;

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

    lblPopSize.setPoint(16, 240);
    delete lblPopSize.render();
    cbPopSize.setPoint(lblPopSize.getX() + lblPopSize.getWidth() + 5, 240);

    lblTitle.setPoint(8, 16);

    GuiState::onResize(m_width, m_height);
}

bool NewGameMenu::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args)
{
    if(src == &btnStart)
    {
        MapGenerator::setAssets(assets);

        GameMap *map = MapGenerator::RandomMap(currentDim->getWidth(), currentDim->getHeight());

        GameState *state = new GameState(assets, map, currentPopLimit);
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
    if(src == &cbMapSize)
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
    else if(src == &cbPopSize)
    {
        if(args->getSelection() == &voSmallPop)
        {
            currentPopLimit = smallPop;
        }
        else if(args->getSelection() == &voMediumPop)
        {
            currentPopLimit = mediumPop;
        }
        else if(args->getSelection() == &voLargePop)
        {
            currentPopLimit = largePop;
        }
        else if(args->getSelection() == &voUnlimited)
        {
            currentPopLimit = unlimitedPop;
        }
    }
}

void NewGameMenu::initComponents()
{
    voSmall = ValueObject(0, "Small");
    voMedium = ValueObject(1, "Medium");
    voLarge = ValueObject(2, "Large");

    voSmallPop = ValueObject(0, "150");
    voMediumPop = ValueObject(1, "250");
    voLargePop = ValueObject(2, "500");
    voUnlimited = ValueObject(3, "Unlimited");

    btnBack.setCaption("Back");
    btnStart.setCaption("Start Game");

    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("New Game");

    lblMapSize.setCaption("Map Size :");

    cbMapSize.add(&voSmall);
    cbMapSize.add(&voMedium);
    cbMapSize.add(&voLarge);

    lblPopSize.setCaption("Population Limit :");

    cbPopSize.add(&voSmallPop);
    cbPopSize.add(&voMediumPop);
    cbPopSize.add(&voLargePop);
    cbPopSize.add(&voUnlimited);

    add(&btnBack);
    add(&btnStart);
    add(&lblTitle);
    add(&lblMapSize);
    add(&cbMapSize);

    add(&lblPopSize);
    add(&cbPopSize);

    cbMapSize.subscribe(this);
    cbPopSize.subscribe(this);
    btnBack.subscribe(this);
    btnStart.subscribe(this);
}
