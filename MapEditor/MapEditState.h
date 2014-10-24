#ifndef MAPEDITSTATE_H
#define MAPEDITSTATE_H

#include <GuiState.h>
#include <SpriteLibrary.h>
#include <vector>
#include <KeyEventListener.h>
#include "MEMap.h"
#include "EditItem.h"


class MapEditState :
        public StiGame::Gui::GuiState,
        public StiGame::KeyEventListener
{
public:
    MapEditState(MEMap *m_map);
    virtual ~MapEditState();

    void onStart(void);
    void onResize(int m_width, int m_height);
    void handleEvent(StiGame::KeyEventThrower *src, StiGame::KeyEventArgs *args);

protected:
    static const char* NONE_TEXTURE;
    std::vector< std::string > availableTextures;
    StiGame::SpriteLibrary *sprites;
    void scanTextures(void);
    MEMap *map;
    MapItem *mapItem;
    EditItem editItem;

};

#endif // MAPEDITSTATE_H
