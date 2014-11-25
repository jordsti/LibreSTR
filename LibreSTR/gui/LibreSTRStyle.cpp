#include "LibreSTRStyle.h"

using namespace StiGame;
using namespace Gui;

LibreSTRStyle::LibreSTRStyle() : Style()

{
    //ctor
    background.setRGB(26, 26, 26);
    foreground.setRGB(245, 230, 190);

    highlightBackground.setRGB(235, 147, 59);
    highlightForeground.setRGB(18, 18, 18);
}

LibreSTRStyle::~LibreSTRStyle()
{
    //dtor
}
