#ifndef MAPEDITMAINMENU_H
#define MAPEDITMAINMENU_H


#include <GuiState.h>
#include <Button.h>
#include <List.h>
#include "MapFileVO.h"
#include <EventListener.h>
#include <SelectionEventListener.h>
#include <vector>
#include <Label.h>

class MapEditMainMenu :
        public StiGame::Gui::GuiState,
        public StiGame::EventListener,
        public StiGame::Gui::SelectionEventListener
{
public:
    static const int BTN_WIDTH = 200;
    static const int BTN_HEIGHT = 25;

    MapEditMainMenu();
    virtual ~MapEditMainMenu();
    void onResize(int m_width, int m_height);
    bool handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt);
    void handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *args);
    void unload(void);
protected:
    void initComponents(void);

    StiGame::Gui::Button btnNewMap;
    StiGame::Gui::Button btnLoadMap;
    StiGame::Gui::List listMaps;
    StiGame::Gui::Button btnQuit;
    StiGame::Gui::Label lblTitle;

    std::vector<MapFileVO*> mapFiles;
    MapFileVO *selectedMap;
};

#endif // MAPEDITMAINMENU_H
