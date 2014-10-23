#ifndef FILE_H
#define FILE_H

#include "Entry.h"

namespace FS
{
class File :
        public Entry
{
public:
    File(std::string m_name, std::string m_parent);
    virtual ~File();
    EntryType type(void);
    bool endsWith(std::string m_suffix);
private:

};
}

#endif // FILE_H
