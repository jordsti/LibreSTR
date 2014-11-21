#ifndef CONSOLE_H
#define CONSOLE_H

#include <Item.h>
#include <TextBox.h>
#include <vector>
#include "ILogStream.h"

struct ConsoleLine
{
    std::string text;
    StiGame::Surface *surface;
};

class Console :
        public StiGame::Gui::Item,
        public ILogStream
{
public:
    static const int DEFAULT_LINE_HEIGHT = 13;
    static const int DEFAULT_LINE_BUFFER = 60;

    Console();
    virtual ~Console();
    StiGame::Surface* render(void);

    void pushLine(std::string line);

    void resized(void);
    void prune(void);

private:
    int lineBuffer;
    int lineHeight;
    StiGame::Surface* consoleHeader;
    StiGame::Color consoleBackground;
    StiGame::Color linesBackground;
    StiGame::Color textColor;
    StiGame::Gui::TextBox textBox;

    std::vector< ConsoleLine* > lines;
    StiGame::Font *font;
};

#endif // CONSOLE_H
