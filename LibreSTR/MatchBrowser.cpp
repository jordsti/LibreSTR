#include "MatchBrowser.h"
#include "MainMenu.h"


MatchVO::MatchVO(STRData::Match *m_match) :
    StiGame::Gui::ValueObject(m_match->getId(), m_match->getName())
{
    match = m_match;
}

MatchVO::~MatchVO()
{

}

STRData::Match* MatchVO::getMatch(void)
{
    return match;
}

MatchBrowser::MatchBrowser(AssetManager *m_assets) :
    StiGame::Gui::GuiState(),
    //127.0.0.1 for testing purpose at the moment
    client("127.0.0.1", STRData::MATCH_MASTER_PORT)
{
    assets = m_assets;
    initComponents();

    refreshing = false;
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

    matchesList.setDimension(350, 200);
    matchesList.setPoint(8, 70);

    btnRefresh.setCaption("Refresh");

    btnNewGame.setCaption("New Game");

    add(&lblTitle);
    add(&btnBack);
    add(&btnRefresh);
    add(&btnNewGame);
    add(&matchesList);

    btnBack.subscribe(this);
    btnRefresh.subscribe(this);
    btnNewGame.subscribe(this);
}

void MatchBrowser::refreshList(void)
{
    if(client.isCompleted() && !refreshing)
    {
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

    return true;
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
            MatchVO *vo = new MatchVO((*lit));
            matches.push_back(vo);
            matchesList.add(vo);
        }
    }


    GuiState::onPaint(renderer);
}

void MatchBrowser::onResize(int m_width, int m_height)
{
    btnBack.prerender();
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);

    btnRefresh.prerender();
    btnRefresh.setPoint(btnBack.getX() + btnBack.getWidth() + 10, m_height - btnBack.getHeight() - 8);

    btnNewGame.prerender();
    btnNewGame.setPoint(matchesList.getX(), matchesList.getY() + matchesList.getHeight() + 5);

    lblTitle.setPoint(8, 16);

    GuiState::onResize(m_width, m_height);
}

