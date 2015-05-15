#include "OptionState.h"
#include "MainMenu.h"
#include "ResolutionVO.h"
/* TO DO
 * - add toggle console binding
 * - add show fps binding
 * - save settings !!
 */
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

    tbPlayerName.prerender();
    tbPlayerName.setPoint(lblPlayerName.getX() + lblPlayerName.getWidth() + 5, lblPlayerName.getY());

    lblResolutions.prerender();
    lblResolutions.setPoint(8, lblPlayerName.getY() + lblPlayerName.getHeight() + 10);

    cbResolutions.prerender();
    cbResolutions.setPoint(lblResolutions.getX() + lblResolutions.getWidth() + 5, lblPlayerName.getY() + lblPlayerName.getHeight() + 10);

    btnBack.prerender();
    btnBack.setPoint(16, m_height - btnBack.getHeight() - 8);

    cbResolutions.clearItems();

    cbFullscreen.prerender();

    cbFullscreen.setPoint(8, lblResolutions.getY() + lblResolutions.getHeight() + 10);

    lblMinimap.prerender();
    lblMinimap.setPoint(8, cbFullscreen.getY() + cbFullscreen.getHeight() + 10);

    kbShowMinimap.setPoint(lblMinimap.getX() + lblMinimap.getWidth() + 5, lblMinimap.getY());

    lblPauseGame.prerender();
    lblPauseGame.setPoint(8, lblMinimap.getY() + lblMinimap.getHeight() + 10);

    kbPauseGame.setPoint(lblPauseGame.getX() + lblPauseGame.getWidth() + 5, lblPauseGame.getY());

    lblMoveViewUp.prerender();
    lblMoveViewUp.setPoint(8, lblPauseGame.getY() + lblPauseGame.getHeight() + 10);

    kbMoveViewUp.setPoint(lblMoveViewUp.getX() + lblMoveViewUp.getWidth() + 5, lblMoveViewUp.getY());

    lblMoveViewDown.prerender();
    lblMoveViewDown.setPoint(8, lblMoveViewUp.getY() + lblMoveViewUp.getHeight() + 10);

    kbMoveViewDown.setPoint(lblMoveViewDown.getX() + lblMoveViewDown.getWidth() + 5, lblMoveViewDown.getY());

    lblMoveViewRight.prerender();
    lblMoveViewRight.setPoint(8, lblMoveViewDown.getY() + lblMoveViewDown.getHeight() + 10);

    kbMoveViewRight.setPoint(lblMoveViewRight.getX() + lblMoveViewRight.getWidth() + 5, lblMoveViewRight.getY());

    lblMoveViewLeft.prerender();
    lblMoveViewLeft.setPoint(8, lblMoveViewRight.getY() + lblMoveViewRight.getHeight() + 10);

    kbMoveViewLeft.setPoint(lblMoveViewLeft.getX() + lblMoveViewLeft.getWidth() + 5, lblMoveViewLeft.getY());

    cbFullscreen.setChecked(viewport->getVideoConfig()->isFullscreen());

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

    lblMinimap.setCaption("Show Minimap");

    kbShowMinimap.fromActionMap(assets->getBindings()->getBinding("show_minimap"));
    KeyEventThrower::subscribe(&kbShowMinimap);

    lblPauseGame.setCaption("Pause Game");

    kbPauseGame.fromActionMap(assets->getBindings()->getBinding("pause_game"));
    KeyEventThrower::subscribe(&kbPauseGame);

    lblMoveViewUp.setCaption("Move View Up");
    kbMoveViewUp.fromActionMap(assets->getBindings()->getBinding("view_move_up"));
    KeyEventThrower::subscribe(&kbMoveViewUp);

    lblMoveViewDown.setCaption("Move View Down");
    kbMoveViewDown.fromActionMap(assets->getBindings()->getBinding("view_move_down"));
    KeyEventThrower::subscribe(&kbMoveViewDown);

    lblMoveViewRight.setCaption("Move View Right");
    kbMoveViewRight.fromActionMap(assets->getBindings()->getBinding("view_move_right"));
    KeyEventThrower::subscribe(&kbMoveViewRight);

    lblMoveViewLeft.setCaption("Move View Left");
    kbMoveViewLeft.fromActionMap(assets->getBindings()->getBinding("view_move_left"));
    KeyEventThrower::subscribe(&kbMoveViewLeft);

    btnBack.subscribe(this);

    add(&lblTitle);
    add(&lblPlayerName);
    add(&tbPlayerName);
    add(&lblResolutions);
    add(&cbResolutions);
    add(&cbFullscreen);

    add(&lblMinimap);
    add(&kbShowMinimap);

    add(&lblMoveViewUp);
    add(&kbMoveViewUp);

    add(&lblMoveViewDown);
    add(&kbMoveViewDown);

    add(&lblMoveViewRight);
    add(&kbMoveViewRight);

    add(&lblMoveViewLeft);
    add(&kbMoveViewLeft);

    add(&lblPauseGame);
    add(&kbPauseGame);

    add(&btnBack);
}
