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

Titanium::Titanium(int m_id) :
    IResource(m_id)
{
    //ctor
    name = "Titanium";
    texture = "tba";
    amount = STARTING_AMOUNT;
    type = RT_METAL;
}

IResource* Titanium::clone(void)
{
    return new Titanium(getId());
}

Titanium::~Titanium()
{
    //dtor
}
