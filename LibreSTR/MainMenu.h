#ifndef MAINMENU_H
#define MAINMENU_H
#include <GuiState.h>
#include <EventListener.h>

#include <Label.h>
#include <Button.h>
#include <Image.h>

class MainMenu :
    public StiGame::Gui::GuiState,
    public StiGame::EventListener
{

    public:
        static const int BUTTON_WIDTH;
        static const int BUTTON_HEIGHT;
        MainMenu();
        virtual ~MainMenu();
        void onResize(int m_width, int m_height);
        void handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt);

    protected:
        StiGame::Gui::Label lblTitle;
        StiGame::Gui::Button btnNewGame;
        StiGame::Gui::Button btnQuit;

        StiGame::Gui::Image img;

    private:
        void initComponents(void);
};

#endif // MAINMENU_H
