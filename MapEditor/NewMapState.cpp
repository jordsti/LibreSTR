#include "NewMapState.h"
#include "MapEditMainMenu.h"
using namespace StiGame;
using namespace Gui;

NewMapState::NewMapState() : GuiState()
{
    initComponents();
}

NewMapState::~NewMapState()
{

}

void NewMapState::handleEvent(StiGame::EventThrower *src, StiGame::EventArgs *evt)
{
    if(src == &btnBack)
    {
        MapEditMainMenu *state = new MapEditMainMenu();
        viewport->push(state);
    }
}

void NewMapState::onResize(int m_width, int m_height)
{

    MPoint curpt;

    curpt.setPoint(5, m_height - BTN_HEIGHT - 5);

    btnBack.setPoint(&curpt);
}

void NewMapState::unload()
{
    auto vit(mapSizes.begin()), vend(mapSizes.end());
    //some cleaning
    for(;vit!=vend;++vit)
    {
        listSizes.remove((*vit));
        delete (*vit);
    }
}

void NewMapState::initComponents(void)
{


    MapSizeVO *vo1 = new MapSizeVO(1, Dimension(200, 90));
    MapSizeVO *vo2 = new MapSizeVO(2, Dimension(250, 114));
    MapSizeVO *vo3 = new MapSizeVO(3, Dimension(300, 200));
    MapSizeVO *vo4 = new MapSizeVO(4, Dimension(350, 220));

    mapSizes.push_back(vo1);
    mapSizes.push_back(vo2);
    mapSizes.push_back(vo3);
    mapSizes.push_back(vo4);

    listSizes.setDimension(150, 200);
    listSizes.setPoint(5, 50);
    listSizes.add(vo1);
    listSizes.add(vo2);
    listSizes.add(vo3);
    listSizes.add(vo4);

    listSizes.setSelectedIndex(0);

    lblTitle.setFont(style->getBigFont());
    lblTitle.setCaption("New Map ...");
    lblTitle.setPoint(5, 10);

    btnBack.setFixedSize(BTN_WIDTH, BTN_HEIGHT);
    btnBack.setCaption("Back");
    btnBack.subscribe(this);

    add(&listSizes);
    add(&lblTitle);
    add(&btnBack);
}
