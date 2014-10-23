#ifndef MAPSIZEVO_H
#define MAPSIZEVO_H

#include <ValueObject.h>
#include <Dimension.h>

class MapSizeVO :
        public StiGame::Gui::ValueObject
{
public:
    MapSizeVO(int m_id, StiGame::Dimension dim);
    virtual ~MapSizeVO();
    StiGame::Dimension* getDimension(void);
protected:
    StiGame::Dimension dimension;
};

#endif // MAPSIZEVO_H
