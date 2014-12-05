#include "MainMenu.h"
#include <GamePath.h>
#include "MapGenerator.h"
#include "NewGameMenu.h"
#include "GameState.h"

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

    lblAuthor.setCaption("Created by JordSti - 2014");

    btnNewGame.setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btnNewGame.setCaption("New Game");

    btnQuit.setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    btnQuit.setCaption("Quit");

    img.setImage(StiGame::GamePath::getFilepath(StiGame::AssetRoot, "mainmenu_image.png"));

    add(&lblTitle);
    add(&lblAuthor);
    add(&btnNewGame);
    add(&btnQuit);
    add(&img);

    btnNewGame.subscribe(this);
    btnQuit.subscribe(this);
}

void MainMenu::onStart(void)
{
    viewport->clearPreviousStates();
    running = true;
}

bool MainMenu::handleEvent(EventThrower *src, EventArgs *evt)
{
    if(src == &btnNewGame)
    {
        //todo game state
        //GameState *state = new GameState(assets);
        NewGameMenu *state = new NewGameMenu(assets);
        viewport->push(state);
    }
    else if(src == &btnQuit)
    {
        running = false;
    }

    return false;
}

void MainMenu::onResize(int m_width, int m_height)
{


    //middle the label
    lblTitle.doAutosize();
    lblTitle.setPoint((m_width - lblTitle.getWidth())/2, 20);

    lblAuthor.doAutosize();
    lblAuthor.setPoint(m_width - lblAuthor.getWidth(), m_height - lblAuthor.getHeight());

    btnNewGame.setPoint((m_width - btnNewGame.getWidth())/2, 100);
    btnQuit.setPoint((m_width - btnQuit.getWidth())/2, 100 + BUTTON_HEIGHT + 10);

    img.setPoint((m_width - img.getWidth())/2, 100 + 2*BUTTON_HEIGHT + 25);
}
