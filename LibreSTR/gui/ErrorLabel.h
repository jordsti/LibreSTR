#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <Item.h>
#include <StringRenderer.h>

class ErrorLabel :
        public StiGame::Gui::Item
{
public:
    static const int TICK_MAX;
    ErrorLabel();
    virtual ~ErrorLabel(void);

    StiGame::Surface *render(void);

    void setCaption(std::string m_caption);
    std::string getCaption(void);

    void setFont(StiGame::Font *m_font);

    void setTickMax(int m_tickMax);

private:
    StiGame::Color textColor;
    StiGame::StringRenderer strBuffer;
    std::string caption;
    StiGame::Font *font;
    int tickCount;
    int tickMax;
};

#endif // ERRORLABEL_H
