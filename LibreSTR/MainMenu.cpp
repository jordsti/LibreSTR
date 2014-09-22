#include "MainMenu.h"

MainMenu::MainMenu()
{
    //ctor
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

    btnNewGame.setFixedSize(250, 40);
    btnNewGame.setCaption("New Game");

    add(&lblTitle);
    add(&btnNewGame);
}


void MainMenu::onResize(int m_width, int m_height)
{


    //middle the label
    lblTitle.doAutosize();
    lblTitle.setPoint(( m_width - lblTitle.getWidth() )/2, 20);

    btnNewGame.setPoint((m_width - btnNewGame.getWidth())/2, 100);

}
