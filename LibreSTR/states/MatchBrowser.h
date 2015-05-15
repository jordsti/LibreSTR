#ifndef MATCHBROWSER_H
#define MATCHBROWSER_H

#include <GuiState.h>
#include <Button.h>
#include <Label.h>
#include "MatchMasterClient.h"
#include <EventListener.h>
#include "AssetManager.h"
#include <list>
#include <Table.h>
#include <TableClickEventListener.h>


class MatchBrowser :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener,
        public StiGame::Gui::TableClickEventListener
{
public:
    MatchBrowser(AssetManager *m_assets);
    virtual ~MatchBrowser();

    void onStart(void);
    void onResize(int m_width, int m_height);

    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *args);
    void handleEvent(StiGame::Gui::TableClickEventThrower *src, StiGame::Gui::TableClickEventArgs *args);
    void refreshList(void);

    void onPaint(SDL_Renderer *renderer);
private:
    STRData::Match *selectedMatch;
    void initComponents(void);

    bool refreshing;
    AssetManager *assets;

    StiGame::Gui::Button btnBack;
    StiGame::Gui::Button btnRefresh;
    StiGame::Gui::Button btnNewGame;
    StiGame::Gui::Button btnJoinGame;
    StiGame::Gui::Table matchesTable;
    StiGame::Gui::Label lblTitle;

    MatchMasterClient client;
};

#endif // MATCHBROWSER_H
