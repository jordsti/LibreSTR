#ifndef MAPEDITSTATE_H
#define MAPEDITSTATE_H

#include <GuiState.h>
#include <SpriteLibrary.h>
#include <vector>
#include <KeyEventListener.h>
#include <MouseButtonEventListener.h>
#include <MouseMotionEventListener.h>
#include "MEMap.h"
#include "EditItem.h"


class MapEditState :
        public StiGame::Gui::GuiState,
        public StiGame::KeyEventListener,
        public StiGame::MouseButtonEventListener,
        public StiGame::MouseMotionEventListener
{
public:
    MapEditState(MEMap *m_map);
    virtual ~MapEditState();

    void onStart(void);
    void onResize(int m_width, int m_height);
    void handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args);
    void handleEvent(StiGame::MouseButtonEventThrower *src, StiGame::MouseButtonEventArgs *args);
    void handleEvent(StiGame::MouseMotionEventThrower *src, StiGame::MouseMotionEventArgs *args);
protected:
    static const char* NONE_TEXTURE;
    std::vector< std::string > availableTextures;
    StiGame::SpriteLibrary *sprites;
    void scanTextures(void);
    MEMap *map;
    MapItem *mapItem;
    EditItem editItem;
    StiGame::MPoint selectionStart;
    bool selectionStarted;

};

#endif // MAPEDITSTATE_H
