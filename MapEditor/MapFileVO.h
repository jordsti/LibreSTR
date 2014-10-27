#ifndef MAPFILEVO_H
#define MAPFILEVO_H

#include <ValueObject.h>
#include <Entry.h>

class MapFileVO :
        public StiGame::Gui::ValueObject
{
public:
    MapFileVO(int m_id, StiGame::FS::Entry *m_fileEntry);
    virtual ~MapFileVO();
    StiGame::FS::Entry *getFileEntry(void);

protected:
    StiGame::FS::Entry *fileEntry;
};

#endif // MAPFILEVO_H
