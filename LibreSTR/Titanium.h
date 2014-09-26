#ifndef TITANIUM_H
#define TITANIUM_H
#include "IResource.h"

class Titanium :
    public IResource
{
    public:
        static const int STARTING_AMOUNT;
        Titanium();
        virtual ~Titanium();
        IResource* clone(void);
    protected:
    private:
};

#endif // TITANIUM_H
