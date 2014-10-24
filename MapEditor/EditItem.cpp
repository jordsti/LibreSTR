#include "EditItem.h"

using namespace StiGame;
using namespace Gui;

EditItem::EditItem() : Item("EditItem")
{
    lblPosition.setCaption("Position : 0; 0");
    lblPosition.setPoint(5, 5);
    height = 150;
}

EditItem::~EditItem()
{

}

void EditItem::update(MapItem *item)
{
    Point *pt = item->getPosition();
    std::string pos_str = "Position : ";

    pos_str += std::to_string(pt->getX());
    pos_str += "; ";
    pos_str += std::to_string(pt->getY());

    lblPosition.setCaption(pos_str);
}

Surface* EditItem::render()
{
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);

    Surface *lbl = lblPosition.render();
    buffer->blit(lbl, &lblPosition);
    delete lbl;

    return buffer;
}


