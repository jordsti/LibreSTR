#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "Directory.h"
#include "File.h"
#include <vector>

namespace FS
{

class FileSystem
{
public:
    static std::vector<Entry*> ListDirectory(std::string m_path);

private:
    FileSystem();
};

}

#endif // FILESYSTEM_H
