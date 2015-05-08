#ifndef MATCHBROWSER_H
#define MATCHBROWSER_H

#include <GuiState.h>
#include <Button.h>
#include <List.h>
#include <Label.h>
#include "MatchMasterClient.h"
#include <EventListener.h>
#include "AssetManager.h"
#include <list>

class MatchVO :
        public StiGame::Gui::ValueObject
{
public:
    MatchVO(STRData::Match *m_match);
    virtual ~MatchVO();

    STRData::Match* getMatch(void);

private:
    STRData::Match *match;
};

class MatchBrowser :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener
{
public:
    MatchBrowser(AssetManager *m_assets);
    virtual ~MatchBrowser();

    void onStart(void);
    void onResize(int m_width, int m_height);

    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args);
    void refreshList(void);

    void onPaint(SDL_Renderer *renderer);
private:
    std::list<MatchVO*> matches;
    void initComponents(void);

    bool refreshing;
    AssetManager *assets;

    StiGame::Gui::Button btnBack;
    StiGame::Gui::Button btnRefresh;
    StiGame::Gui::Button btnNewGame;
    StiGame::Gui::List matchesList;
    StiGame::Gui::Label lblTitle;

    MatchMasterClient client;
};

#endif // MATCHBROWSER_H
