#include "TopHud.h"
#include "GamePath.h"
using namespace StiGame;
using namespace Gui;

TopHud::TopHud(AssetManager *m_assets)
{
    assets = m_assets;

    iconMetal.setImage(GamePath::getFilepath(AssetRoot, assets->getMetalIdentity()->getIcon()));
    iconGaz.setImage(GamePath::getFilepath(AssetRoot, assets->getGazIdentity()->getIcon()));

    maximumSize.setHeight(30);
    height = 30;


    lblMetalCount.setCaption("0");
    lblMetalCount.doAutosize();
    lblGazCount.setCaption("0");
    lblGazCount.doAutosize();

    iconMetal.setPoint(5, (height - iconMetal.getHeight())/2);
    lblMetalCount.setPoint(iconMetal.getX() + iconMetal.getWidth() + 5, (height - lblMetalCount.getHeight())/2);

    iconGaz.setPoint(200, (height - iconGaz.getHeight())/2);
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

Surface* TopHud::render(void)
{
    Surface *sur = new Surface(width, height);

    sur->fill(background);

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
