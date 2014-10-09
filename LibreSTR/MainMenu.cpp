#include "MainMenu.h"
#include <GamePath.h>
#include "MapGenerator.h"
#include "NewGameMenu.h"

const int MainMenu::BUTTON_WIDTH = 250;
const int MainMenu::BUTTON_HEIGHT = 40;

using namespace StiGame;

MainMenu::MainMenu(AssetManager *m_assets)
{
    //ctor
    assets = m_assets;
    initComponents();
}

MainMenu::~MainMenu()
{
    //dtor
}


void MainMenu::initComponents(void)
{
    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("Libre STR");

    btnNewGame.setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btnNewGame.setCaption("New Game");

    btnQuit.setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btnQuit.setCaption("Quit");

    img.setImage(StiGame::GamePath::getFilepath(StiGame::AssetRoot, "mainmenu_image.png"));

    add(&lblTitle);
    add(&btnNewGame);
    add(&btnQuit);
    add(&img);

    btnNewGame.subscribe(this);
    btnQuit.subscribe(this);
}


void MainMenu::handleEvent(EventThrower *src, EventArgs *evt)
{
    if(src == &btnNewGame)
    {
        //todo game state
        //GameState *state = new GameState(assets, MapGenerator::RandomMap(300, 200));
        NewGameMenu *state = new NewGameMenu();
        viewport->push(state);
    }
    else if(src == &btnQuit)
    {
        running = false;
    }
}

void MainMenu::onResize(int m_width, int m_height)
{


    //middle the label
    lblTitle.doAutosize();
    lblTitle.setPoint((m_width - lblTitle.getWidth())/2, 20);

    btnNewGame.setPoint((m_width - btnNewGame.getWidth())/2, 100);
    btnQuit.setPoint((m_width - btnQuit.getWidth())/2, 100 + BUTTON_HEIGHT + 10);

    img.setPoint((m_width - img.getWidth())/2, 100 + 2*BUTTON_HEIGHT + 10);
}
