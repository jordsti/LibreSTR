#ifndef MAINMENU_H
#define MAINMENU_H
#include <GuiState.h>

#include <Label.h>
#include <Button.h>

class MainMenu :
    public StiGame::Gui::GuiState
{
    public:
        MainMenu();
        virtual ~MainMenu();
        void onResize(int m_width, int m_height);
    protected:
        StiGame::Gui::Label lblTitle;
        StiGame::Gui::Button btnNewGame;
    private:
        void initComponents(void);
};

#endif // MAINMENU_H
