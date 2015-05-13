#include "MatchBrowser.h"
#include "MainMenu.h"
#include <ValueObject.h>
#include "GameClient.h"

MatchBrowser::MatchBrowser(AssetManager *m_assets) :
    StiGame::Gui::GuiState(),
    client(m_assets->getMasterServer(), STRData::MATCH_MASTER_PORT)
{
    assets = m_assets;
    initComponents();

    refreshing = false;
    selectedMatch = nullptr;
}

MatchBrowser::~MatchBrowser()
{

}

void MatchBrowser::onStart(void)
{
    running = true;
}

void MatchBrowser::initComponents(void)
{
    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("Multiplayer Game");

    btnBack.setCaption("Back");

    matchesTable.setDimension(700, 400);
    matchesTable.setPoint(8, 70);

    matchesTable.addColumn("Name", 250);
    matchesTable.addColumn("Players", 150);
    matchesTable.addColumn("Host", 200);
    matchesTable.addColumn("Port", 100);

    btnRefresh.setCaption("Refresh");

    btnNewGame.setCaption("New Game");

    btnJoinGame.setCaption("Join Game");

    add(&lblTitle);
    add(&btnBack);
    add(&btnRefresh);
    add(&btnNewGame);
    add(&matchesTable);
    add(&btnJoinGame);

    btnBack.subscribe(this);
    btnRefresh.subscribe(this);
    btnNewGame.subscribe(this);
    btnJoinGame.subscribe(this);

    matchesTable.subscribe(this);
}

void MatchBrowser::refreshList(void)
{
    if(client.isCompleted() && !refreshing)
    {
        selectedMatch = nullptr;
        client.fetchMatches();
        refreshing = true;
    }
}

bool MatchBrowser::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args)
{
    if(src == &btnBack)
    {
        MainMenu *nextState = new MainMenu(assets);
        viewport->push(nextState);
    }
    else if(src == &btnRefresh)
    {
        refreshList();
    }
    else if(src == &btnNewGame)
    {
        //todo
        //new multiplayer game state
    }
    else if(src == &btnJoinGame)
    {
        if(selectedMatch != nullptr)
        {
            //todo
            //new lobby state here
            GameClient *gameClient = new GameClient(selectedMatch->getHost(), selectedMatch->getPort());
            gameClient->start();
        }
    }

    return true;
}

void MatchBrowser::handleEvent(StiGame::Gui::TableClickEventThrower *src, StiGame::Gui::TableClickEventArgs *args)
{
    StiGame::Gui::TableRow *row = args->getRow();
    if(row != nullptr)
    {
        STRData::Match *match = client.getMatchById(row->getValueObject()->getId());
        if(match != nullptr)
        {
            selectedMatch = match;
        }
    }
}

void MatchBrowser::onPaint(SDL_Renderer *renderer)
{
    if(refreshing && client.isCompleted())
    {
        refreshing = false;

        std::list<STRData::Match*> _matches = client.getMatches();

        auto lit(_matches.begin()), lend(_matches.end());
        for(;lit!=lend;++lit)
        {
            STRData::Match *m = (*lit);
            StiGame::Gui::TableRow *row = matchesTable.newRow();
            row->setValue(0, m->getName());
            std::string players = std::to_string(m->getCurrentPlayers()) + "/" + std::to_string(m->getMaxPlayers());
            row->setValue(1, players);
            row->setValue(2, m->getHost());
            row->setValue(3, std::to_string(m->getPort()));

            StiGame::Gui::ValueObject *vo = new StiGame::Gui::ValueObject(m->getId(), m->getName());
            row->setValueObject(vo);
        }
    }

    btnJoinGame.setVisible(selectedMatch != nullptr);


    GuiState::onPaint(renderer);
}

void MatchBrowser::onResize(int m_width, int m_height)
{
    btnBack.prerender();
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);

    btnRefresh.prerender();
    btnRefresh.setPoint(btnBack.getX() + btnBack.getWidth() + 10, m_height - btnBack.getHeight() - 8);

    btnNewGame.prerender();
    btnNewGame.setPoint(matchesTable.getX(), matchesTable.getY() + matchesTable.getHeight() + 5);

    btnJoinGame.prerender();
    btnJoinGame.setPoint(matchesTable.getX() + btnNewGame.getWidth() + 10, matchesTable.getY() + matchesTable.getHeight() + 5);

    lblTitle.setPoint(8, 16);

    GuiState::onResize(m_width, m_height);
}

