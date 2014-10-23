#include "MapFileVO.h"

MapFileVO::MapFileVO(int m_id, FS::Entry *m_fileEntry) :
    StiGame::Gui::ValueObject(m_id, m_fileEntry->getNameWithoutExtension())
{
    fileEntry = m_fileEntry;
}

MapFileVO::~MapFileVO()
{

}

FS::Entry* MapFileVO::getFileEntry(void)
{
    return fileEntry;
}
