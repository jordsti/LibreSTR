#ifndef VFRESOURCE_H
#define VFRESOURCE_H

#include "IResource.h"

class VFResource :
    public IResource
{
    public:
        VFResource(int m_id, IResource *parent);
        VFResource(IResource *parent);
        VFResource(std::string var_file);
        virtual ~VFResource();
        IResource* clone(void);
        IResource* create(void);
    protected:
        void fromVarFile(std::string var_file);
    private:
};

#endif // VFRESOURCE_H
