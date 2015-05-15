#ifndef RESOLUTIONVO_H
#define RESOLUTIONVO_H

#include <ValueObject.h>
#include <Dimension.h>

class ResolutionVO :
        public StiGame::Gui::ValueObject
{
public:
    ResolutionVO(int id, std::string caption, StiGame::Dimension *dim);
    virtual ~ResolutionVO();

    StiGame::Dimension* getDimension(void);

private:
    StiGame::Dimension dimension;
};

#endif // RESOLUTIONVO_H
