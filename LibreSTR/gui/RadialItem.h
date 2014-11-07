#ifndef RADIALITEM_H
#define RADIALITEM_H

#include <string>
#include <ValueObject.h>

class RadialItem :
        public StiGame::Gui::ValueObject
{
public:
    RadialItem(int m_id, std::string m_name, std::string m_icon, std::string m_iconHover);
    virtual ~RadialItem();

    std::string getIcon(void);
    std::string getIconHover(void);

private:

    std::string icon;
    std::string iconHover;
};

#endif // RADIALITEM_H
