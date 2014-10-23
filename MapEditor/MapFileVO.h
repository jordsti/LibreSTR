#ifndef MAPFILEVO_H
#define MAPFILEVO_H

#include <ValueObject.h>
#include <Entry.h>

class MapFileVO :
        public StiGame::Gui::ValueObject
{
public:
    MapFileVO(int m_id, FS::Entry *m_fileEntry);
    virtual ~MapFileVO();
    FS::Entry *getFileEntry(void);

protected:
    FS::Entry *fileEntry;
};

#endif // MAPFILEVO_H
