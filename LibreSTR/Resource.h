#ifndef IRESOURCE_H
#define IRESOURCE_H

#include <string>

class ResourceIdentity;

enum ResourceType {
    RT_NOT_DEFINED = 0,
    RT_METAL = 1,
    RT_GAZ = 2
};

class Resource
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
