#include "MapSizeVO.h"

using namespace StiGame;
using namespace Gui;

MapSizeVO::MapSizeVO(int m_id, StiGame::Dimension dim) : ValueObject(m_id, "")
{
    dimension = dim;
    text = std::to_string(dimension.getWidth()) + "x" + std::to_string(dimension.getHeight());
}

MapSizeVO::~MapSizeVO()
{

}

StiGame::Dimension* MapSizeVO::getDimension(void)
{
    return &dimension;
}
