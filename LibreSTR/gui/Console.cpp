#include "Console.h"
#include <GamePath.h>
#include "PRect.h"
#include <iostream>

using namespace StiGame;
using namespace Gui;

Console::Console()
{
    font = new Font(GamePath::getFilepath(AssetRoot, "font-fw.ttf").c_str(), 12);
    consoleBackground.setRGBA(50, 50, 50, 150);
    linesBackground.setRGBA(70, 70, 70, 150);
    textColor.setRGBA(255, 255, 255, 255);


    background = &consoleBackground;
    foreground = &textColor;

    consoleHeader = font->renderText("Console", foreground);

    lineHeight = DEFAULT_LINE_HEIGHT;
    lineBuffer = DEFAULT_LINE_BUFFER;

    textBox.setFont(font);
    textBox.setForeground(foreground);
    textBox.setBackground(background);
    textBox.setHeight(20);
}

void Console::resized(void)
{
    textBox.setWidth(width - 10);
}

Console::~Console()
{
    //todo
    auto vit(lines.begin()), vend(lines.end());
    for(;vit!=vend;++vit)
    {
        delete (*vit)->surface;
        delete (*vit);
    }

    delete consoleHeader;
    delete font;
}

void Console::prune(void)
{
    if(lines.size() > lineBuffer)
    {
        //some little cleaning
        auto vit(lines.begin()), vend(lines.end());
        int i=0;
        int indexKeep = lines.size() - lineBuffer;
        for(;vit!=vend;++vit)
        {
            if(i < indexKeep)
            {
                delete (*vit)->surface;
                delete (*vit);

                lines.erase(vit);
            }

            i++;
        }
    }
}

void Console::pushLine(std::string line)
{
    ConsoleLine *cl = new ConsoleLine();
    cl->text = line;
    cl->surface = font->renderText(line, &textColor);
    lines.push_back(cl);

    prune();
}

StiGame::Surface* Console::render(void)
{
    Surface *buffer = new Surface(width, height);
    buffer->fill(background);

    //drawing header

    int c_y = 2;

    MPoint dst (2, c_y);

    c_y += consoleHeader->getHeight() + 4;

    buffer->blit(consoleHeader, &dst);

    //inside rect

    Rectangle iRect (5, c_y, width - 10, height - (c_y + 5 + textBox.getHeight()));

    buffer->fillRect(&iRect, &linesBackground);

    int lineCount = height - (c_y + 5);
    lineCount /= lineHeight;

    if(lineCount > lines.size())
    {
        auto vit(lines.begin()), vend(lines.end());
        for(;vit!=vend;++vit)
        {
            dst.setPoint(7, c_y);
            buffer->blit((*vit)->surface, &dst);
            c_y += lineHeight;
        }
    }
    else
    {
        //inverse drawing
        c_y = height - (textBox.getHeight() + 5);
        int offset = lines.size() - 1;
        for(int i=0; i < lineCount; i++)
        {
            int index = offset - i;

            ConsoleLine *cl = lines[index];

            dst.setPoint(7, c_y);
            buffer->blit(cl->surface, &dst);
            c_y -= lineHeight;
        }

    }

    //drawing textbox
    dst.setPoint(5, height - (5 + textBox.getHeight()));

    Surface *tb = textBox.render();
    buffer->blit(tb, &dst);
    delete tb;

    //border
    PRect border (0, 0, width, height);
    buffer->draw(&border, foreground);

    return buffer;

}
