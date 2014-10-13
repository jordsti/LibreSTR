#ifndef RESOURCE_H
#define RESOURCE_H

#include "IResource.h"

class ResourceIdentity;

class Resource :
        public IResource
{
    public:
        Resource(ResourceIdentity *m_identity);
        Resource(ResourceIdentity *m_identity, int m_id);
        virtual ~Resource();

        int getId(void);
        std::string getName(void);
        std::string getTexture(void);
        std::string getIcon(void);
        ResourceType getType(void);
        int getAmount(void);
        void setAmount(int m_amount);

        Resource* clone(void);

        ResourceIdentity* getIdentity(void);

    protected:
        int amount;


    private:
        int _id;
        static int _currentId;
        int GetCurrendId(void);
        ResourceIdentity *_identity;


};

#endif // IRESOURCE_H
