#include "ResolutionVO.h"

ResolutionVO::ResolutionVO(int id, std::string caption, StiGame::Dimension *dim) :
    StiGame::Gui::ValueObject(id, caption),
    dimension(dim)
{

}

ResolutionVO::~ResolutionVO()
{

}

StiGame::Dimension* ResolutionVO::getDimension(void)
{
    return &dimension;
}
