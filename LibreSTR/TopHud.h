#ifndef TOPHUD_H
#define TOPHUD_H

#include <Item.h>
#include <Label.h>

class TopHud :
    public StiGame::Gui::Item
{
public:
    TopHud();
    virtual ~TopHud();

    StiGame::Surface* render(void);
private:
    StiGame::Gui::Label lblMetalCount;
    StiGame::Gui::Label lblGazCount;
    StiGame::Color textColor;
};

#endif // TOPHUD_H
