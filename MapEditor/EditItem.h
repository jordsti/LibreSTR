#ifndef EDITITEM_H
#define EDITITEM_H
#include "Label.h"
#include "MapItem.h"
class EditItem :
        public StiGame::Gui::Item
{
public:
    EditItem();
    virtual ~EditItem();

    void update(MapItem *item);

    StiGame::Surface* render(void);
protected:
    StiGame::Gui::Label lblPosition;
};

#endif // EDITITEM_H
