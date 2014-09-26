#include "Titanium.h"

const int Titanium::STARTING_AMOUNT = 1000;

Titanium::Titanium() :
    IResource()
{
    //ctor
    name = "Titanium";
    texture = "tba";
    amount = STARTING_AMOUNT;
    type = RT_METAL;
}

IResource* Titanium::clone(void)
{
    return new Titanium();
}

Titanium::~Titanium()
{
    //dtor
}
