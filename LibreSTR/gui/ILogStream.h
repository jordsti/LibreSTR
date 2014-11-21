#ifndef ILOGSTREAM_H
#define ILOGSTREAM_H

#include <string>

class ILogStream
{
public:
    ILogStream();
    virtual ~ILogStream();

    virtual void pushLine(std::string line) = 0;
};

#endif // ILOGSTREAM_H
