#ifndef IRESOURCE_H
#define IRESOURCE_H

#include <string>

enum ResourceType {
    RT_NOT_DEFINED = 0,
    RT_METAL = 1,
    RT_GAZ = 2
};

class IResource
{
    public:
        virtual ~IResource();

        int getId(void);
        std::string getName(void);
        std::string getTexture(void);
        ResourceType getType(void);
        int getAmount(void);
        void setAmount(int m_amount);

        virtual IResource* clone(void) = 0;

    protected:
        IResource();
        IResource(int m_id);

        std::string name;
        int amount;
        std::string texture;
        ResourceType type;

    private:
        int _id;
        static int _currentId;
        int GetCurrendId(void);

};

#endif // IRESOURCE_H
