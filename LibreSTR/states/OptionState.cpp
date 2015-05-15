#include "OptionState.h"
#include "MainMenu.h"
#include "ResolutionVO.h"

OptionState::OptionState(AssetManager *m_assets)
{
    assets = m_assets;
    initComponents();
}

OptionState::~OptionState()
{

}

void OptionState::onResize(int m_width, int m_height)
{
    lblTitle.setPoint(8, 16);
    lblTitle.prerender();

    lblPlayerName.prerender();
    lblPlayerName.setPoint(8, lblTitle.getY() + lblTitle.getHeight() + 10);

    tbPlayerName.setPoint(lblPlayerName.getX() + 5, lblPlayerName.getY());

    lblResolutions.prerender();
    lblResolutions.setPoint(8, lblPlayerName.getY() + lblPlayerName.getHeight() + 10);

    cbResolutions.setPoint(lblResolutions.getX() + lblResolutions.getWidth() + 5, lblPlayerName.getY() + lblPlayerName.getHeight() + 10);

    btnBack.prerender();
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);

    cbResolutions.clearItems();

    cbFullscreen.prerender();

    cbFullscreen.setPoint(8, lblResolutions.getY() + 10);

    //filling resolution
    std::list<StiGame::Dimension> resolutions = viewport->GetSupportedResolution();
    int i=0;
    auto rit(resolutions.begin()), rend(resolutions.end());
    for(;rit!=rend;++rit)
    {
        StiGame::Dimension dim = (*rit);

        std::string str_res = std::to_string(dim.getWidth()) + "x" + std::to_string(dim.getHeight());
        ResolutionVO *vo = new ResolutionVO(i, str_res, &dim);

        cbResolutions.add(vo);

        if(viewport->getWidth() == dim.getWidth() && viewport->getHeight() == dim.getHeight())
        {
            cbResolutions.setSelectedItem(vo);
        }

        i++;
    }

}

bool OptionState::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt)
{
    if(src == &btnBack)
    {
        MainMenu *state = new MainMenu(assets);
        viewport->push(state);
    }
}

void OptionState::handleEvent(StiGame::Gui::SelectionEventThrower *src, StiGame::Gui::SelectionEventArgs *evt)
{
    if(src == &cbResolutions)
    {
        //todo
        //change resolution settings and save them !
    }
}

void OptionState::initComponents(void)
{
    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("Option");

    lblPlayerName.setCaption("Player Name : ");

    tbPlayerName.setDimension(200, 22);
    tbPlayerName.setText(assets->getOptions()->getValue("playerName"));

    btnBack.setCaption("Back");

    lblResolutions.setCaption("Resolution : ");

    cbFullscreen.setCaption("Fullscreen");
    cbFullscreen.setChecked(viewport->getVideoConfig()->isFullscreen());

    add(&lblTitle);
    add(&lblPlayerName);
    add(&tbPlayerName);
    add(&lblResolutions);
    add(&cbResolutions);
    add(&cbFullscreen);
    add(&btnBack);
}
