#include "TopHud.h"
#include "GamePath.h"
#include "PRect.h"
using namespace StiGame;
using namespace Gui;

TopHud::TopHud(AssetManager *m_assets, Player *m_player)
{
    assets = m_assets;
    player = m_player;

    iconMetal.setImage(GamePath::getFilepath(AssetRoot, assets->getMetalIdentity()->getIcon()));
    iconGaz.setImage(GamePath::getFilepath(AssetRoot, assets->getGazIdentity()->getIcon()));

    maximumSize.setHeight(30);
    height = 30;


    lblMetalCount.setCaption("0");
    lblMetalCount.doAutosize();
    lblGazCount.setCaption("0");
    lblGazCount.doAutosize();

    iconMetal.setPoint(20, (height - iconMetal.getHeight())/2);
    lblMetalCount.setPoint(iconMetal.getX() + iconMetal.getWidth() + 5, (height - lblMetalCount.getHeight())/2);

    iconGaz.setPoint(215, (height - iconGaz.getHeight())/2);
    lblGazCount.setPoint(iconGaz.getX() + iconGaz.getWidth() + 5, (height - lblMetalCount.getHeight())/2);

    textColor.setRGB(255, 255, 255);

    lblMetalCount.setForeground(&textColor);
    lblGazCount.setForeground(&textColor);

    background = new Color(0, 0, 0, 230);

    items.push_back(&iconMetal);
    items.push_back(&lblMetalCount);
    items.push_back(&iconGaz);
    items.push_back(&lblGazCount);
}

TopHud::~TopHud()
{

}

void TopHud::updateHud(void)
{
    std::string nMetal = std::to_string(player->getMetalCount());
    std::string nGaz = std::to_string(player->getGazCount());

    if(nMetal != lblMetalCount.getCaption())
    {
        lblMetalCount.setCaption(nGaz);
    }

    if(nGaz != lblGazCount.getCaption())
    {
        lblGazCount.setCaption(nGaz);
    }

}

Surface* TopHud::render(void)
{
    updateHud();
    Surface *sur = new Surface(width, height);

    sur->fill(background);

    PRect pColorRect;
    pColorRect.setDimension(15, 15);
    pColorRect.setX(2);
    pColorRect.setY((height - pColorRect.getHeight())/2);

    sur->fill(&pColorRect, player->getColor());

    Surface *itemBuffer;
    auto lit(items.begin()), lend(items.end());
    for(;lit!=lend;++lit)
    {
        itemBuffer = (*lit)->render();
        sur->blit(itemBuffer, (*lit));
        delete itemBuffer;
    }

    return sur;
}
