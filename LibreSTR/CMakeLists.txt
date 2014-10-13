cmake_minimum_required(VERSION 2.8)
project(LibreSTR)

set(SOURCE_FILES main.cpp
    AssetManager.cpp
    Building.cpp
    BuildingIdentity.cpp
    BuildingSprite.cpp
    GameMap.cpp
    GameObject.cpp
    GameOverlay.cpp
    GameState.cpp
    IResource.cpp
    ITileMap.cpp
    Resource.cpp
    LibreSTRStyle.cpp
    MainMenu.cpp
    MapGenerator.cpp
    MiniMap.cpp
    NewGameMenu.cpp
    Player.cpp
    PlayerMap.cpp
    Tile.cpp
    TopHud.cpp
    ToggleMiniMapAction.cpp
    ToggleShowFPSAction.cpp
    ResourceIdentity.cpp
    Unit.cpp
    UnitSprite.cpp
    ViewMoveAction.cpp
)

configure_file(VersionConfig.h.in ${PROJECT_SOURCE_DIR}/LibreSTRVersion.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} mingw32 STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
endif(WIN32)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
