#ifndef NEWMAPSTATE_H
#define NEWMAPSTATE_H

#include <GuiState.h>
#include "MapSizeVO.h"
#include <vector>
#include <List.h>
#include <Label.h>
#include <Button.h>
#include <EventListener.h>
#include <CheckBox.h>

class NewMapState :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener
{
public:
    static const int BTN_WIDTH = 200;
    static const int BTN_HEIGHT = 25;

    NewMapState();
    virtual ~NewMapState();
    void onResize(int m_width, int m_height);
    void handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt);
    void unload(void);
protected:
    void initComponents(void);
    int mapWidth;
    int mapHeight;
    std::vector<MapSizeVO*> mapSizes;
    StiGame::Gui::List listSizes;
    StiGame::Gui::Label lblTitle;
    StiGame::Gui::Button btnBack;
};

#endif // NEWMAPSTATE_H
