#include "MapFileVO.h"

MapFileVO::MapFileVO(int m_id, StiGame::FS::Entry *m_fileEntry) :
    StiGame::Gui::ValueObject(m_id, m_fileEntry->getNameWithoutExtension())
{
    fileEntry = m_fileEntry;
}

MapFileVO::~MapFileVO()
{

}

StiGame::FS::Entry* MapFileVO::getFileEntry(void)
{
    return fileEntry;
}
