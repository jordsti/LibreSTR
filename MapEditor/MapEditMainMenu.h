#ifndef MAPEDITMAINMENU_H
#define MAPEDITMAINMENU_H


#include <GuiState.h>
#include <Button.h>
#include <List.h>

class MapEditMainMenu :
        StiGame::Gui::GuiState
{
public:
    MapEditMainMenu();
    virtual ~MapEditMainMenu();
    void onResize(int m_width, int m_height);
protected:
    void initComponents(void);

    StiGame::Gui::Button btnNewMap;
    StiGame::Gui::Button btnLoadMap;
    StiGame::Gui::List listMaps;
    StiGame::Gui::Button btnQuit;

};

#endif // MAPEDITMAINMENU_H
