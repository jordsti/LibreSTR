#include "HydrocarbonGaz.h"

const int HydrocarbonGaz::STARTING_AMOUNT = 1500;

HydrocarbonGaz::HydrocarbonGaz() :
    IResource()
{
    //ctor
    name = "Hydrocarbon Gaz";
    amount = STARTING_AMOUNT;
    type = RT_GAZ;
    texture = "tba";
}

HydrocarbonGaz::HydrocarbonGaz(int m_id) :
    IResource(m_id)
{
    //ctor
    name = "Hydrocarbon Gaz";
    amount = STARTING_AMOUNT;
    type = RT_GAZ;
    texture = "tba";
}

IResource* HydrocarbonGaz::clone(void)
{
    return new HydrocarbonGaz(getId());
}

HydrocarbonGaz::~HydrocarbonGaz()
{
    //dtor
}
