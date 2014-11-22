#include "MultiSelectionPanel.h"
#include "GamePath.h"
using namespace StiGame;
using namespace Gui;

MultiSelectionPanel::MultiSelectionPanel() : Item("MultiSelectionPanel")
{
    height = 120;
    width = 200;
    assets = nullptr;
}

MultiSelectionPanel::~MultiSelectionPanel()
{

}

StiGame::Surface* MultiSelectionPanel::render(void)
{
    //todo
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);

    return buffer;
}

void MultiSelectionPanel::setAssets(AssetManager *m_assets)
{
    assets = m_assets;

    //loading icon
    GroundUnitIdentity *worker = assets->getWorkerIdentity();
    Surface *icon =  new Surface(GamePath::getFilepath(AssetRoot, worker->getIcon()));
    unitIcons.insert(std::make_pair(worker->getName(), icon));

}

void MultiSelectionPanel::clearSelection(void)
{
    units.clear();
}

void MultiSelectionPanel::addGroundUnit(GroundUnit *unit)
{
    units.push_back(unit);
}
