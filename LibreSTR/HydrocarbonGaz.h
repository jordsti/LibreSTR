#ifndef HYDROCARBONGAZ_H
#define HYDROCARBONGAZ_H
#include "IResource.h"

class HydrocarbonGaz :
    public IResource
{
    public:
        static const int STARTING_AMOUNT;
        HydrocarbonGaz();
        virtual ~HydrocarbonGaz();
        IResource* clone(void);
    protected:
    private:
};

#endif // HYDROCARBONGAZ_H
