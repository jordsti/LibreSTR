#include "TopHud.h"
#include "GamePath.h"
#include "PRect.h"
using namespace StiGame;
using namespace Gui;

TopHud::TopHud(AssetManager *m_assets, Player *m_player)
{
    assets = m_assets;
    player = m_player;

    leftImage = new Surface(GamePath::getFilepath(AssetRoot, "tophud_left.png"));
    bgImage = new Surface(GamePath::getFilepath(AssetRoot, "tophud_bg.png"));
    rightImage = new Surface(GamePath::getFilepath(AssetRoot, "tophud_right.png"));

    bg = nullptr;

    iconMetal.setImage(GamePath::getFilepath(AssetRoot, assets->getMetalIdentity()->getIcon()));
    iconGaz.setImage(GamePath::getFilepath(AssetRoot, assets->getGazIdentity()->getIcon()));

    maximumSize.setHeight(30);
    height = 30;


    lblMetalCount.setCaption("0");
    lblMetalCount.doAutosize();
    lblGazCount.setCaption("0");
    lblGazCount.doAutosize();

    lblPopulation.setCaption("0 / 0");
    lblPopulation.doAutosize();

    iconMetal.setPoint(20, (height - iconMetal.getHeight())/2);
    lblMetalCount.setPoint(iconMetal.getX() + iconMetal.getWidth() + 5, (height - lblMetalCount.getHeight())/2);

    iconGaz.setPoint(215, (height - iconGaz.getHeight())/2);
    lblGazCount.setPoint(iconGaz.getX() + iconGaz.getWidth() + 5, (height - lblMetalCount.getHeight())/2);

    textColor.setRGB(255, 255, 255);

    lblMetalCount.setForeground(&textColor);
    lblGazCount.setForeground(&textColor);

    lblPopulation.setPoint( lblGazCount.getX() + 150, (height - lblPopulation.getHeight())/2);

    background = new Color(0, 0, 0, 230);

    items.push_back(&iconMetal);
    items.push_back(&lblMetalCount);
    items.push_back(&iconGaz);
    items.push_back(&lblGazCount);
    items.push_back(&lblPopulation);
}

TopHud::~TopHud()
{
    delete leftImage;
    delete bgImage;
    delete rightImage;

    if(bg != nullptr)
    {
        delete bg;
    }
}

void TopHud::updateHud(void)
{
    std::string nMetal = std::to_string(player->getMetalCount());
    std::string nGaz = std::to_string(player->getGazCount());

    if(nMetal != lblMetalCount.getCaption())
    {
        lblMetalCount.setCaption(nMetal);
    }

    if(nGaz != lblGazCount.getCaption())
    {
        lblGazCount.setCaption(nGaz);
    }

    std::string pop = std::to_string(player->getCurrentPopulation()) + " / " + std::to_string(player->getMaxPopulation());

    if(pop != lblPopulation.getCaption())
    {
        lblPopulation.setCaption(pop);
    }

}

void TopHud::resized()
{
    renderBackground();
}

void TopHud::renderBackground()
{
    if(bg != nullptr)
    {
        delete bg;
    }

    bg = new Surface(width, height);
    int ix = 0;

    while(ix < width)
    {
        MPoint pt (ix, 0);
        if(ix == 0)
        {
            bg->blit(leftImage, &pt);
            ix += leftImage->getWidth();
        }
        else if(ix < width - rightImage->getWidth())
        {
            bg->blit(bgImage, &pt);
            ix += bgImage->getWidth();
        }
        else
        {
            pt.setX(width - rightImage->getWidth());
            bg->blit(rightImage, &pt);
            ix += rightImage->getWidth();
        }
    }
}

Surface* TopHud::render(void)
{

    if(bg == nullptr)
    {
        renderBackground();
    }

    updateHud();
    Surface *sur = new Surface(width, height);
    Point ptDst (0,0);
    sur->fill(background);
    sur->blit(bg, &ptDst);

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
